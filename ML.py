from sklearn import svm
from sklearn.neighbors import KNeighborsClassifier
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import BaggingClassifier

def generate_data(taux):
    fichier=open("/Users/MathieuRita/Desktop/MODAL/INF473-x16/proteinesderemi.txt", "r")
    L=fichier.readlines()
    window_size=2*int(L[0])+1
    cell_size=int(L[1]) #pm
    nb_prot=int(L[2])

    data=np.empty([0,(window_size)**3])
    labels=np.empty(0)

    for ind_prot in range(taux) :
        cpt=0
        nb_line=int(L[cpt+3])
        for ind_line in range(cpt+4,cpt+4+nb_line) :
             bbdata=np.empty(0)
             line=L[ind_line].split("\t")
             for i in range(0,len(line)-1) :
                 bbdata=np.append(bbdata,np.array(int(line[i])))
             labels=np.append(labels,np.array(int(line[len(line)-1])))
             data=np.append(data, [bbdata], axis=0)
        cpt+=nb_line
        print(ind_prot)

    fichier.close()
    return(data,labels,window_size,cpt)

def generate_pred():
    fichier=open("/Users/MathieuRita/Desktop/MODAL/INF473-x16/testpourcomparer.txt", "r")
    L=fichier.readlines()
    window_size=2*int(L[0])+1
    cell_size=int(L[1]) #pm
    nb_prot=int(L[2])

    data=np.empty([0,(window_size)**3])
    labels=np.empty(0)

    for ind_prot in range(nb_prot) :
        cpt=0
        nb_line=int(L[cpt+3])
        for ind_line in range(cpt+4,cpt+4+nb_line) :
             bbdata=np.empty(0)
             line=L[ind_line].split("\t")
             for i in range(0,len(line)-1) :
                 bbdata=np.append(bbdata,np.array(int(line[i])))
             labels=np.append(labels,np.array(int(line[len(line)-1])))
             data=np.append(data, [bbdata], axis=0)
        cpt+=nb_line
        print(ind_prot)

    fichier.close()
    return(data,labels,window_size,cpt)

#train_data,train_labels,window_size,ech_size=generate_data(20)
#pred_data,pred_labels,window_size,ech_size=generate_pred()

#np.array des donnees d entrainement,#np.array des labels de dtype=np.int32 normalement

# train_data=np.load("datatraining.npy")
# train_labels=np.load("labelstraining.npy")
pred_data=np.load("datapred.npy")
pred_labels=np.load("labelspred.npy")

# knn = KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',metric_params=None, n_jobs=1, n_neighbors=5, p=2,weights='uniform')
# knn.fit(train_data, train_labels)
#
# pred=knn.predict(pred_data)

# nb_1=0
# nb_0=0
# L=len(train_labels_load)
# for i in range(L) :
#     if train_labels_load[i]==1.0 :
#         nb_1+=1
#     if train_labels_load[i]==0.0 :
#         nb_0+=1
#
# tdata=np.empty([0,5**3])
# tlabels=np.empty(0)
# c=0
# d=0
# i=0
# while d<nb_1 :
#     if train_labels_load[i]==1.0 :
#         d+=1
#         tdata=np.append(tdata,[train_data_load[i]],axis=0)
#         tlabels=np.append(tlabels,train_labels_load[i])
#
#     if train_labels_load[i]==0.0 and c<int(nb_1*2):
#         c+=1
#         tdata=np.append(tdata,[train_data_load[i]],axis=0)
#         tlabels=np.append(tlabels,train_labels_load[i])
#     i+=1
#     print(c,d)
# print(train_data_load.shape,tdata.shape,tlabels.shape)
#
# train_data=tdata
# train_labels=tlabels

def balance(train_data_load,train_labels_load):
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
    e=0
    c=0
    d=0
    i=0
    while d<nb_1 :
        if train_labels_load[i]==1.0 :
            d+=1
            tdata=np.append(tdata,[train_data_load[i]],axis=0)
            tlabels=np.append(tlabels,train_labels_load[i])

        if train_labels_load[i]==0.0 and c<int(nb_1*1.5):
            e+=1
            if e>2000 :
                c+=1
                tdata=np.append(tdata,[train_data_load[i]],axis=0)
                tlabels=np.append(tlabels,train_labels_load[i])
        i+=1
    return (tdata,tlabels)

def test(deb,fin):
    clf = svm.SVC(kernel='linear', C=1.0, random_state=0)
    for i in range(deb,fin):
        print("dataset"+str(i)+".npy")
        train_data_load=np.load("dataset"+str(i)+".npy")  #np.array des donnees d entrainement,
        train_labels_load=np.load("labelset"+str(i)+".npy")   #np.array des labels de dtype=np.int32 normalement
        tdata,tlabels=balance(train_data_load,train_labels_load)
        clf.fit(tdata, tlabels)
    pred=clf.predict(pred_data)
    # clf = svm.SVC(kernel='poly', degree=3, C=C)
    # clf=svm.LinearSVC(C=C,class_weight={1.0 : nb_0, 0.0 : nb_1})
    # clf = KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',metric_params=None, n_jobs=1, n_neighbors=5, p=2,weights='uniform')
    # clf = BaggingClassifier(KNeighborsClassifier(),max_samples=0.5, max_features=0.5)
    # clf = RandomForestClassifier(n_estimators=10)
    # clf.fit(train_data[int(L*ta):int(L*(ta+0.1))], train_labels[int(L*ta):int(L*(ta+0.1))])
    # clf.fit(training,labeling)


    #
    #######Test######
    tot=0
    reu=0
    nbun=0
    nbcool=0
    vrai=0
    for i in range(len(pred)):
        tot+=1
        if pred[i]==1.0 :
            nbun+=1
        if pred_labels[i]==1.0 :
            vrai+=1
        if pred[i]==pred_labels[i] :
            reu+=1
            if pred[i]==1.0 :
                nbcool+=1
    print(reu, tot, vrai,nbun,nbcool)

# test(0,3)

def conca():
    train_data_load=np.load("dataset"+str(0)+".npy")  #np.array des donnees d entrainement,
    train_labels_load=np.load("labelset"+str(0)+".npy")   #np.array des labels de dtype=np.int32 normalement
    tdata,tlabels=balance(train_data_load,train_labels_load)
    data,label=tdata,tlabels
    for i in range(0,50):
        train_data_load=np.load("dataset"+str(i)+".npy")  #np.array des donnees d entrainement,
        train_labels_load=np.load("labelset"+str(i)+".npy")   #np.array des labels de dtype=np.int32 normalement
        tdata,tlabels=balance(train_data_load,train_labels_load)
        data=np.append(data, tdata, axis=0)
        label=np.append(label, tlabels, axis=0)
    np.save("datach",data)
    np.save("labelch",label)
    print(data.shape,label.shape)

def tra():
    clf = svm.SVC(kernel='linear', C=1.0, random_state=0)
    clf.fit(np.load("datach.npy"), np.load("labelch.npy"))
    pred=clf.predict(pred_data)
    tot=0
    reu=0
    nbun=0
    nbcool=0
    vrai=0
    for i in range(len(pred)):
        tot+=1
        if pred[i]==1.0 :
            nbun+=1
        if pred_labels[i]==1.0 :
            vrai+=1
        if pred[i]==pred_labels[i] :
            reu+=1
            if pred[i]==1.0 :
                nbcool+=1
    print(reu, tot, vrai,nbun,nbcool)

#tra()
conca()
