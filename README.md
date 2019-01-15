# Prediction of the binding sites of a protein using a CNN and a ligand-protein database

The aim of the project was to predict the binding sites of proteins. The project only used the geometrical structure of the proteins. Starting from the ligand-protein database we built a dataset composed with a large number of proteins where each atom was given a proximity coefficient (the minimum distance between each atom of the protein and the ligand). Eventually, we classified the sites using a deep learning neural-network adapted to geometrical issues (CNN with 3D convolutions).

Repositories and files :

- PDB : dataset which comes from the "Proteins data base"
- Data : precomputed proteins (ie. proteins with their proximity coefficients)
- datach.npy & label.npy : precomputed features gathered in numpy arrays
- Elements : C++ files that compute the protein coefficients
- CNN.py : neural-network that calculates the predictions
- predict***.txt : some predictions
- Results : example of images that can be obtained with the predictions

Result :

https://www.linkedin.com/feed/update/urn:li:activity:6385496694305492992/
