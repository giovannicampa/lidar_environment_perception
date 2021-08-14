#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

class PCLSegmentation {       // The class

private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    ros::Publisher pub_; 

public:

    // Constructor
    PCLSegmentation() { 
        sub_ = nh_.subscribe<pcl::PointCloud<pcl::PointXYZRGB> > ("/camera/camera_modelet_manager/camera/depth_registered/points", 5, &PCLSegmentation::callback, this);
        pub_ = nh_.advertise<sensor_msgs::PointCloud2> ("pcl_cluster", 500);
    }

    // Subscriber callback
    void callback(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& msg)
    {
    }

};

int main(int argc, char **argv)
{
    // Node initialisation
    ros::init(argc, argv, "pcl_segmentation");
    PCLSegmentation PCLSegmentationObject;
    ros::spin();
}