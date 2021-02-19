# plot training and test data
fig, axs = plt.subplots(2)
# train
axs[0].scatter(xtrData, ytrData,None,"red")
axs[0].set_title("training data")
# test
axs[1].set_title("test data")
axs[1].scatter(xteData, yteData)



