/*
 * given gyro_data in rad/s, accel_data in m/s/s, and delta t in seconds, return an attitude in radians (relative to the power on state)
 */
float[] filter(float[] gyro_data, float[] accel_data, float dt);