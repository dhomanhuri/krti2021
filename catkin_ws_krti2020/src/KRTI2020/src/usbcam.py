#<launch>
  <node name="usb_cam2" pkg="usb_cam2" type="usb_cam_node2" output="screen" >
    <param name="video_device" value="/dev/video0" />
    <param name="image_width" value="640" />
    <param name="image_height" value="480" />
    <param name="pixel_format" value="yuyv" />
    <param name="camera_frame_id" value="usb_cam2" />
    <param name="io_method" value="mmap"/>
  </node>
  <node name="image_view" pkg="image_view" type="image_view" respawn="false" ou$
    <remap from="image" to="/usb_cam2/image_raw"/>
    <param name="autosize" value="true" />
  </node>
#</launch>

