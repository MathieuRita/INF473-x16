
import numpy as np


def generate_data(taux):
    fichier=open("/Users/MathieuRita/Desktop/MODAL/INF473-x16/proteinesderemi.txt", "r")
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


data,labels,window_size,cpt=generate_data(300)
np.save("dataset",data)
np.save("labelset",labels)
