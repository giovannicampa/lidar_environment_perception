#! /usr/bin/python3

import glob
import os

import numpy as np
import PointNetClassifier
# import tensorflow as tf
# import trimesh
# from matplotlib import pyplot as plt
# from tensorflow import keras
# from tensorflow.keras import layers


# tf.random.set_seed(1234)


# DATA_DIR = tf.keras.utils.get_file(
#     "modelnet.zip",
#     "http://3dvision.princeton.edu/projects/2014/3DShapeNets/ModelNet10.zip",
#     extract=True,
# )
# DATA_DIR = os.path.join(os.path.dirname(DATA_DIR), "ModelNet10")

# mesh = trimesh.load(os.path.join(DATA_DIR, "chair/train/chair_0001.off"))
# mesh.show()

# points = mesh.sample(2048)

# fig = plt.figure(figsize=(5, 5))
# ax = fig.add_subplot(111, projection="3d")
# ax.scatter(points[:, 0], points[:, 1], points[:, 2])
# ax.set_axis_off()
# plt.show()


from sensor_msgs.msg import PointCloud2
import numpy as np
import rospy
import ros_numpy

class ClassiferNode():

    def __init__(self):

        self.classifier = PointNetClassifier()
        self.publiser = rospy.Publisher("pcl_classified", PointCloud2, queue_size=1)
        self.subsciber = rospy.Subscriber("pcl_cluster", PointCloud2, self.classify_callback)


    def classify_callback(self, msg):
        pc = ros_numpy.numpify(msg)
        points = grad.Variable(pc[0]).cuda()
        pred, _ = self.classifier.classify(points)
        print(pred)


if __name__ == "__main__":
    rospy.init_node('classifier_node', anonymous=True)
    navigator = ClassiferNode()
    rospy.spin()
