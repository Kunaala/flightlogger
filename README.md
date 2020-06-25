### Flightlogger
#### Subscribes to vital topics from Mavros ROS publisher
#### Topics:
1. /mavros/imu/data                   : Message type-sensor_msgs/Imu
2. /mavros/global_position/global     : Message type-sensor_msgs/NavSatFix
3. /mavros/global_position/rel_alt    : Message type-std_msgs/Float64

Parameters considered for Logging
1.  Orientation: in quaternions
2. Angular Velocity: 
3. Linear acceleration
4. Geo-coordinates: latitude,longitude 
5. Relative altitude:

##### Logs data in CSV format

### License
[MIT](https://choosealicense.com/licenses/mit/)
