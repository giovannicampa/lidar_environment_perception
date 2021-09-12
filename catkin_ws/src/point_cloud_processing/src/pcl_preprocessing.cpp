#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>

#include <pcl_ros/point_cloud.h>

class PCLSegmentation
{ // The class

private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    ros::Publisher pub_;

public:
    // Constructor
    PCLSegmentation()
    {
        sub_ = nh_.subscribe<sensor_msgs::PointCloud2>("velodyne_points", 5, &PCLSegmentation::callback, this);
        pub_ = nh_.advertise<sensor_msgs::PointCloud2>("pcl_cluster", 500);
    }

    // Subscriber callback
    void callback(const sensor_msgs::PointCloud2ConstPtr &msg)
    {

        // Convert ROS msg PointCloud2 type to PCL PointCloud2 type
        pcl::PCLPointCloud2 pointCloud2;
        pcl_conversions::toPCL(*msg, pointCloud2);
        pcl::PointCloud<pcl::PointXYZ>::Ptr PointCloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromPCLPointCloud2(pointCloud2, *PointCloud);


        sensor_msgs::PointCloud2::Ptr passthrough_filtered (new sensor_msgs::PointCloud2);

        pcl::PassThrough<pcl::PointXYZ> passThrough;
        passThrough.setInputCloud(PointCloud);
        passThrough.setFilterFieldName("z");
        passThrough.setFilterLimits(-0.3, 2);
        passThrough.filter(*PointCloud);

        pcl::VoxelGrid<pcl::PointXYZ> sor;
        sor.setInputCloud(PointCloud);
        sor.setLeafSize(0.1,0.1,0.1);
        sor.filter(*PointCloud);


        pcl::PCLPointCloud2 pcl_temp;
        pcl::toPCLPointCloud2(*PointCloud, pcl_temp);

        // Convert PCL PointCloud2 to ROS msg PointCloud2 type
        sensor_msgs::PointCloud2 PointCloud_AfterVoxelGrid;
        pcl_conversions::fromPCL(pcl_temp, PointCloud_AfterVoxelGrid);
        PointCloud_AfterVoxelGrid.header = msg->header;


        pub_.publish(PointCloud_AfterVoxelGrid);

    }
};

int main(int argc, char **argv)
{
    // Node initialisation
    ros::init(argc, argv, "pcl_segmentation");
    PCLSegmentation PCLSegmentationObject;
    ros::spin();
}