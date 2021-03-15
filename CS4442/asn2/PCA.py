import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

facesData = np.loadtxt( 'faces.dat' )
row = 400
pix = 64
col = pix*pix

# Reshape the data
data = facesData.reshape(row, col)
print("(a) Display the 100th Image")
image = 100
# rotate and display image
plt.imshow(np.rot90(data[image].reshape(pix, pix),3), cmap="gray")
plt.show()

# remove mean from data
mean = data.mean()
center = data - mean
print("(b) remove mean and Display the 100th Image")
# rotate and display image
plt.imshow(np.rot90(center[image].reshape(pix, pix),3), cmap="gray")
plt.show()

pca = PCA()
pca.fit(center)
# get sorted eigenvalues
eigenValues = pca.explained_variance_
eigenIndex = np.arange(row)
# plot sorted eigen values
print("(c) sorted eigenvalues")
plt.plot(eigenIndex, eigenValues)
plt.show()

lastEigen = eigenValues[row-1]
print("(d) Last Eigenvalue: ", lastEigen)

# principle components to keep
eigenSum = sum(eigenValues)
plt.plot(np.cumsum(pca.explained_variance_ratio_))
plt.title("(e) Dimensionality")
plt.xlabel("compoenents")
plt.ylabel("variance")
plt.show()

# top 5 leading eigenvectors
print("(f) leading eigenvectors")
components = pca.components_
for i in range(0,5):
    plt.imshow(np.rot90(components[i].reshape(pix, pix),3), cmap="gray")
    plt.show()
    
# reconstructed images
principals = [10,100,200,399]
for comp in principals:
    print("displaying reconstructed image with component = ",comp)
    pca = PCA(n_components = comp)
    transform = pca.fit_transform(center)
    inverse = pca.inverse_transform(transform)
    plt.imshow(np.rot90(inverse[image].reshape(pix, pix),3), cmap="gray")
    plt.show()