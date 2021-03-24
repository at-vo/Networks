#function for 2D gaussian value
def gaus(x, y, sigma):
    return np.exp(-1. * (x**2 + y**2) / (2 * sigma** 2) ) / (2 * np.pi * sigma**2)

# make a 2D Gaussian Kernel 
def makeKernel(sigma, size):
    size = int(size) // 2
    x, y = np.mgrid[-size:size + 1, -size:size + 1]
    kernel = gaus(x, y, sigma)
    return kernel

# seperate the kernel into two 1D kernels
def seperate(kernel): 
    i, j = np.unravel_index(np.abs(kernel).argmax(), kernel.shape)
    kRow = kernel[:, j, None]
    kCol = kernel[None, i, :] / kernel[i, j]
    return kRow, kCol

# implement seperable convolve 
def sepConvolve(img, row, col):
    return signal.convolve2d(signal.convolve2d(img, row), col)