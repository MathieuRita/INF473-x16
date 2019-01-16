###### PRELIMINAIRE ########

"""1) IMPORT
- importation des bibliotheque
2) Generer les donnees
- a partir d'un fichier txt fonction de creation et de sauvegarde dun fichier npy qui contient le dataset par groupe de 5 prot
- fonction qui concatene les petits tableaux
- fonction qui permet de reequilibrer le jeu de DONNEES
3) CNN classifier
- succession des couches de neurones
- mode training
- mode eval
- mode prediction
4) fonction d entrainement
5) fonction de prediction
6) instructions de test
- entrainement-prediction-analyse des donnees obtenues
7) critere d evaluation
8) exportations des donnees
- exportation des donnees en fichier txt pour etre traite par la suite.
9) Instructions"""

######## IMPORT ########

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
import numpy as np
import tensorflow as tf

tf.logging.set_verbosity(tf.logging.INFO)

######### LOADING DATAS #########

def generate_data(taux,adresse_fichier_txt):
    fichier=open(adresse_fichier_txt, "r")
    L=fichier.readlines()
    window_size=2*int(L[0])+1
    cell_size=int(L[1]) #pm
    nb_prot=int(L[2])

    data=np.empty([0,(window_size)**3])
    labels=np.empty(0)

    a=0
    j=0
    cpt=0
    for ind_prot in range(taux) :
        print(L[cpt+3])
        nb_line=int(L[cpt+3])
        for ind_line in range(cpt+4,cpt+4+nb_line) :
             bbdata=np.empty(0)
             line=L[ind_line].split("\t")
             for i in range(0,len(line)-1) :
                 bbdata=np.append(bbdata,np.array(int(line[i])))
             labels=np.append(labels,np.array(int(line[len(line)-1])))
             data=np.append(data, [bbdata], axis=0)
        cpt+=nb_line+1
        print(cpt)
        j+=1
        print(ind_prot,j,data.shape)
        if j==5 :
            np.save("dataset"+str(a),data)
            np.save("labelset"+str(a),labels)
            print("save !")
            a+=1
            j=0
            data=np.empty([0,(window_size)**3])
            labels=np.empty(0)

    fichier.close()
    return(data,labels,window_size,cpt)

def balance(train_data_load,train_labels_load,rate):
    nb_1=0
    nb_0=0
    L=len(train_labels_load)
    for i in range(L) :
        if train_labels_load[i]==1.0 :
            nb_1+=1
        if train_labels_load[i]==0.0 :
            nb_0+=1

    print(nb_1)
    tdata=np.empty([0,5**3])
    tlabels=np.empty(0)
    c=0
    d=0
    i=0
    while d<nb_1 :
        if train_labels_load[i]==1.0 :
            d+=1
            tdata=np.append(tdata,[train_data_load[i]],axis=0)
            tlabels=np.append(tlabels,train_labels_load[i])

        if train_labels_load[i]==0.0 and c<int(nb_1*rate):
            c+=1
            tdata=np.append(tdata,[train_data_load[i]],axis=0)
            tlabels=np.append(tlabels,train_labels_load[i])
        i+=1
    return (tdata,tlabels)

def concatenation(deb,fin,dataname,labelname):
    train_data_load=np.load("dataset"+str(deb)+".npy")  #np.array des donnees d entrainement,
    train_labels_load=np.load("labelset"+str(deb)+".npy")   #np.array des labels de dtype=np.int32 normalement
    tdata,tlabels=balance(train_data_load,train_labels_load)
    data,label=tdata,tlabels
    for i in range(deb+1,fin):
        train_data_load=np.load("dataset"+str(i)+".npy")  #np.array des donnees d entrainement,
        train_labels_load=np.load("labelset"+str(i)+".npy")   #np.array des labels de dtype=np.int32 normalement
        tdata,tlabels=balance(train_data_load,train_labels_load)
        data=np.append(data, tdata, axis=0)
        label=np.append(label, tlabels, axis=0)
    np.save(dataname,data)
    np.save(labelname,label)

def create_dataset(dataname,labelname,adresse_fichier_txt):
    generate_data(300,adresse_fichier_txt)
    concatenation(0,300,dataname,labelname)

######## CNN CLASSIFIER ########

# Fonction qui retourne un array[taille de l echantillon, 2] qui pour chaque element, met dans la case 0 (pas actif) ou 1 (actif). Ensuite selon le mode souhaite, on peut entrainer ou predire

def cnn_model_fn(features, labels, mode):

    ######## CREATION DES COUCHES DE NEURONES ########

    # Input Layer
    input_layer = tf.reshape(tf.cast(features["x"],tf.float32), [-1, 5, 5, 5, 1])
    # A priori on aura ici une grille 3D de pixels de taille 5*5*5 en couleur unique donc channel, -1 signifie qu on ne definie pas ici la taille du lot. Ca nous permet de considerer la taille du lot comme une hyperparametre

    # 1st convolutional layer
    conv1 = tf.layers.conv3d(inputs=input_layer, filters=32, kernel_size=[2, 2, 2], padding="same", activation=tf.nn.relu)
    # kernel_size prend en args la taille x,y,z de la fenetre de convolution. Il faudra adapter a ce qu on a.
    
    print("Coucou")
    conv1=tf.Print(conv1,
                   [conv1],
                   message="coucou")

    # 1st pooling layer
    pool1 = tf.layers.max_pooling3d(inputs=conv1, pool_size=[2,2,2], strides=2)

    # 2nd convolutional layer
    conv2 = tf.layers.conv3d(inputs=pool1, filters=64, kernel_size=[2, 2, 2], padding="same", activation=tf.nn.relu)

    # 2nd pooling layer
    pool2 = tf.layers.max_pooling3d(inputs=conv2, pool_size=[2,2,2], strides=2)

    # Reduction de la taille de pool2 en deux dimensions pour la suite de la connexion
    pool2_flat = tf.reshape(pool2, [-1, 64])
    # tableau a deux dimensions. -1 s adapte a la taille du lot, L*L*L*64 = hauteur*largeur*profondeur*pool2 channels

    # dense layer
    dense = tf.layers.dense(inputs=pool2_flat, units=1024, activation=tf.nn.relu)
    # outputs = activation(inputs.kernel + bias). 1024 = dimensionality of the output space

    # Dropout
    dropout=tf.layers.dropout(inputs=dense,rate=0.4,training=mode == tf.estimator.ModeKeys.TRAIN)
    # une fraction des donnees est perdue aleatoirement de sorte a eviter l overfitting lors du training. Probleme potentiel avec le training

    # Logits layer
    logits=tf.layers.dense(inputs=dropout, units=2)
    # On cree une derniere couche de 2 neurones (un pour chaque classe 0-1)). Notre output est de taille [taille de l echantillon, 2]

    ######## PREDICTION ########

    predictions = {"classes" : tf.argmax(input=logits, axis=1), "probabilities" : tf.nn.softmax(logits, name="softmax_tensor")}
    # classes : Le argmax n a pas specialement d interet. En fait il repere ou est le 1 entre les classes active/inactive. axis=1 signifie que dans notre tableau a deux dims (taille ech, 2), on cherche dans la deuxieme dimension ou les le 1 de sorte a reperer la classe ou doit etre range l atome.
    # We can derive probabilities from our logits layer by applying softmax activation using tf.nn.softmax

    if mode == tf.estimator.ModeKeys.PREDICT:
        return tf.estimator.EstimatorSpec(mode=mode, predictions=predictions)

    ######## MESURE STATISTIQUE DE PERTE #########
    onehot_labels = tf.one_hot(indices=tf.cast(labels, tf.int32), depth=2)
    loss = tf.losses.softmax_cross_entropy(onehot_labels=onehot_labels, logits=logits)
    # ONEHOT : cast : transforme les labels en des int codes sur 32 bits  / les labels sont les categories 0 ou 1 d entrainement  / onehot cree un tableau de taille [taille de l echantillon, 2] pour pouvoir comparer avec le tableau logits
    # LOSS : calcul la fonction de perte qui est une cross entropy (a chercher)

    ######## TRAINING ##########

    if mode == tf.estimator.ModeKeys.TRAIN:
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.0001)
        # train_op = optimizer.minimize(loss=loss)
        train_op = optimizer.minimize(loss=loss, global_step=tf.train.get_global_step())
        return tf.estimator.EstimatorSpec(mode=mode, loss=loss, train_op=train_op)
    #realisation du training par rapport a la mesure de perte et la condition d optimisation qui minimise la perte

    ######## EVALUATION ########

    eval_metric_ops = {"accuracy": tf.metrics.accuracy(labels=labels, predictions=predictions["classes"])}
    return tf.estimator.EstimatorSpec(mode=mode, loss=loss, eval_metric_ops=eval_metric_ops)

######## TRAINING THE MODEL ########

def training(train_data_load,train_labels_load) :

    #DONNEES
    # train_data, train_labels=balance(train_data_load,train_labels_load)
    train_data=train_data_load
    train_labels=train_labels_load

    #Creation de l estimateur a partir de notre fonction
    CNN_classifier = tf.estimator.Estimator(model_fn=cnn_model_fn, model_dir="/tmp/mnist_convnet_model")

    #Suivi de la progression de l algo
    tensors_to_log = {"probabilities": "softmax_tensor"}
    logging_hook = tf.train.LoggingTensorHook(tensors=tensors_to_log, every_n_iter=400)

    #Training
    train_input_fn = tf.estimator.inputs.numpy_input_fn(x={"x": train_data},y=train_labels,batch_size=100,num_epochs=None,shuffle=True)
    CNN_classifier.train(input_fn=train_input_fn,steps=2, hooks=[logging_hook])
    # train input configure l entrainement pour etre valable avec le .train de CNN_classifier. Le batch_size signifie que le modele va s entrainer sur des sous-echantillons de 100 exemples a chaque fois
    # regler le nombre de steps selon la precision d entrainement que l on veut avoir

######## FAIRE LA PREDICTION ########

def prediction() :
    features = tf.estimator.inputs.numpy_input_fn(x={"x": predict_data},num_epochs=1,shuffle=False)
    CNN_classifier = tf.estimator.Estimator(model_fn=cnn_model_fn, model_dir="/tmp/mnist_convnet_model")
    pred=CNN_classifier.predict(input_fn=features)
    L=[]
    for val in pred :
        L+=[val["classes"]]
    return L

######## EVALUATION ############

def evaluation(pred,predict_labels) :
    tot=0
    reu=0
    nbun=0
    nbcool=0
    vrai=0
    for i in range(len(pred)):
        tot+=1
        if pred[i]==1.0 :
            nbun+=1
        if predict_labels[i]==1.0 :
            vrai+=1
        if pred[i]==predict_labels[i] :
            reu+=1
            if pred[i]==1.0 :
                nbcool+=1
    print(reu, tot, vrai,nbun,nbcool)

def evaluation2(pred,predict_labels) :
    eval_input_fn = tf.estimator.inputs.numpy_input_fn(x={"x": eval_data},y=eval_labels,num_epochs=1,shuffle=False)
    eval_results = CNN_classifier.evaluate(input_fn=eval_input_fn)
    print(eval_results)

######## EXPORTATIONS DES DONNEES ############

def generate_pred():
    fichier=open("/Users/MathieuRita/Desktop/MODAL/INF473-x16/predict_5bw4_complex.txt", "r")
    L=fichier.readlines()
    window_size=2*int(L[0])+1
    cell_size=int(L[1]) #pm
    ox=float(L[2])
    oy=float(L[3])
    oz=float(L[4])
    nx=int(L[5])
    ny=int(L[6])
    nz=int(L[7])
    nb_line=int(L[8])

    data=np.empty([0,(window_size)**3])

    for ind_line in range(9,9+nb_line) :
         bbdata=np.empty(0)
         line=L[ind_line].split("\t")
         for i in range(0,len(line)-1) :
             bbdata=np.append(bbdata,np.array(int(line[i])))
         data=np.append(data, [bbdata], axis=0)

    fichier.close()
    return(data,cell_size,ox,oy,oz,nx,ny,nz)

def exportation(filename,cell_size, ox, oy, oz, nx, ny, nz, label) :
    "voxeSize puis coordonnees de l'origine puis le nombre de voxel en X, en Y et en Z Puis les 0 et les 1 dans l'ordre d'une triple boucle classique ie d'abord x puis y puis z !"
    file = open(filename, "w")
    file.write(str(voxesize)+" "+str(ox)+" "+str(oy)+" "+str(oz)+" "+str(nx)+" "+str(ny)+" "+str(nz)+" ")
    for i in range(len(label)):
        file.write(str(label[i])+" ")
    file.close()

######## INSTRUCTIONS ############

# predict_data = np.load("datatst.npy") #donnees a predire
# predict_labels=np.load("labeltst.npy")
train_data_load=np.load("datach.npy")  #np.array des donnees d entrainement,
train_labels_load=np.load("labelch.npy")   #np.array des labels de dtype=np.int32 normalement
# eval_data=  #np.array des donnees qui permettent d evaluer notre algo
# eval_labels=  #np.array des labels d evaluation de dtype=np.int32

def correction(pred):
    for i in range(1,len(pred)-1):
        if pred[i]==1:
            if pred[i-1]==0 and pred[i+1]==0 :
                pred[i]=0
    return pred


#training(train_data_load,train_labels_load)
# pred=prediction()
# evaluation(pred,predict_labels)
# pred=correction(pred)
# evaluation(pred,predict_labels)

training(train_data_load,train_labels_load)
data,voxesize,ox,oy,oz,nx,ny,nz=generate_pred()
predict_data=data
predict=prediction()
predict=correction(predict)
exportation("test.txt",voxesize,ox,oy,oz,nx,ny,nz,predict)
