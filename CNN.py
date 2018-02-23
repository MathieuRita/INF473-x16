######## IMPORT ########

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

# Imports
import numpy as np
import tensorflow as tf

tf.logging.set_verbosity(tf.logging.INFO)

###############################

######## CNN CLASSIFIER ########

# Fonction qui retourne un array[taille de l'échantillon, 2] qui pour chaque élément, met dans la case 0 (pas actif) ou 1 (actif). Ensuite selon le mode souhaité, on peut entrainer ou prédire

def cnn_model_fn(features, labels, mode):
    
    ######## CREATION DES COUCHES DE NEURONES ########
    
    # Input Layer
    input_layer = tf.reshape(features["x"], [-1, L, L, L, 1])
    # A priori on aura ici une grille 3D de pixels de taille L*L*L en couleur unique donc channel, -1 signifie qu'on ne définie pas ici la taille du lot. Ca nous permet de considérer la taille du lot comme une hyperparamètre

    # 1st convolutional layer
    conv1 = tf.layers.conv3d(inputs=input_layer, filters=32, kernel_size=[5, 5, 5], padding="same", activation=tf.nn.relu)
    # kernel_size prend en args la taile x,y,z de la fenêtre de convolution. Il faudra adapter à ce qu'on a.

    # 1st pooling layer
    pool1 = tf.layers.max_pooling3d(inputs=conv1, pool_size=[2,2,2], strides=2)

    # 2nd convolutional layer
    conv2 = tf.layers.conv3d(inputs=pool1, filters=64, kernel_size=[5, 5, 5], padding="same", activation=tf.nn.relu)
    
    # 2nd pooling layer
    pool2 = tf.layers.max_pooling3d(inputs=conv2, pool_size=[2,2,2], strides=2)

    # Réduction de la taille de pool2 en deux dimensions pour la suite de la connexion
    pool2_flat = tf.reshape(pool2, [-1, L*L*L*64])
    # tableau à deux dimensions. -1 s'adapte à la taille du lot, L*L*L*64 = hauteur*largeur*profondeur*pool2 channels

    # dense layer
    dense = tf.layers.dense(inputs=pool2_flat, units=1024, activation=tf.nn.relu)
    # outputs = activation(inputs.kernel + bias). 1024 = dimensionality of the output space

    # Dropout
    dropout=tf.layers.dropout(inputs=dense,rate=0.4,training=mode == tf.estimator.ModeKeys.TRAIN)
    # une fraction des données est perdue aléatoirement de sorte à éviter l'overfitting lors du training. Problème potentiel avec le training
            
    # Logits layer
    logits=tf.layers.dense(inputs=dropout, units=2)
    # On crée une dernière couche de 2 neurones (un pour chaque classe 0-1)). Notre output est de taille [taille de l'échantillon, 2]

    ######## PREDICTION ########

    predictions = {"classes" : tf.argmax(input=logits, axis=1), "probabilities" : tf.nn.softmax(logits, name="softmax_tensor")}
    # classes : Le argmax n'a pas spécialement d'intérêt. En fait il repère où est le 1 entre les classes active/inactive. axis=1 signifie que dans notre tableau à deux dims (taille ech, 2), on cherche dans la deuxième dimension où les le 1 de sorte à repérer la classe où doit être rangé l'atome.
    # We can derive probabilities from our logits layer by applying softmax activation using tf.nn.softmax

    if mode == tf.estimator.ModeKeys.PREDICT:
        return tf.estimator.EstimatorSpec(mode=mode, predictions=predictions)

    ######## MESURE STATISTIQUE DE PERTE #########

    onehot_labels = tf.one_hot(indices=tf.cast(labels, tf.int32), depth=2)
    loss = tf.losses.softmax_cross_entropy(onehot_labels=onehot_labels, logits=logits)
    # ONEHOT : cast : transforme les labels en des int codés sur 32 bits ; les labels sont les catégories 0 ou 1 d'entrainement ; onehot crée un tableau de taille [taille de l'échantillon, 2] pour pouvoir comparer avec le tableau logits
    # LOSS : calcul la fonction de perte qui est une cross entropy (à chercher)

    ######## TRAINING ##########

    if mode == tf.estimator.ModeKeys.TRAIN:
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.001)
        train_op = optimizer.minimize(loss=loss, global_step=tf.train.get_global_step())
        return tf.estimator.EstimatorSpec(mode=mode, loss=loss, train_op=train_op)
    #réalisation du training par rapport à la mesure de perte et la condition d'optimisation qui minimise la perte

    ######## EVALUATION ########

    eval_metric_ops = {"accuracy": tf.metrics.accuracy(labels=labels, predictions=predictions["classes"])}
    return tf.estimator.EstimatorSpec(mode=mode, loss=loss, eval_metric_ops=eval_metric_ops)

######## LOADING DATAS ########

train_data= ???? #np.array des données d'entrainement
train_labels= ???? #np.array des labels de dtype=np.int32 normalement
eval_data= ???? #np.array des données qui permettent d'évaluer notre algo
eval_labels= ???? #np.array des labels d'évaluation de dtype=np.int32
predict_data = ??? #données à prédire

######## TRAINING THE MODEL ########

def training() :

    #Création de l'estimateur à partir de notre fonction
    CNN_classifier = tf.estimator.Estimator(model_fn=cnn_model_fn)

    #Suivi de la progression de l'algo
    tensors_to_log = {"probabilities": "softmax_tensor"}
    logging_hook = tf.train.LoggingTensorHook(tensors=tensors_to_log, every_n_iter=50)

    #Training
    train_input_fn = tf.estimator.inputs.numpy_input_fn(x={"x": train_data},y=train_labels,batch_size=100,num_epochs=None,shuffle=True)
    CNN_classifier.train(input_fn=train_input_fn,steps=20000,hooks=[logging_hook])
    # train input configure l'entrainement pour être valable avec le .train de CNN_classifier. Le batch_size signifie que le modèle va s'entrainer sur des sous-échantillons de 100 exemples à chaque fois
    # règler le nombre de steps selon la précision d'entrainement que l'on veut avoir

    #Evaluation
    eval_input_fn = tf.estimator.inputs.numpy_input_fn(x={"x": eval_data},y=eval_labels,num_epochs=1,shuffle=False)
    eval_results = CNN_classifier.evaluate(input_fn=eval_input_fn)
    print(eval_results)

######## FAIRE LA PREDICTION ########

def prediction() :
    predict_input_fn = tf.estimator.inputs.numpy_input_fn(x={"x": predict_data},num_epochs=1,shuffle=False)
    print(CNN_classifier.predict(input_fn=features, hooks=[logging_hook]))



