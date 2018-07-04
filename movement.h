#ifndef MOVEMENT
#define MOVEMENT

#define FRONT_LEFT_LIFT() setServoAngle(0, 180)
#define FRONT_LEFT_LOWER() setServoAngle(0, 90)
#define FRONT_LEFT_HIP(n) setServoAngle(1, n)

#define FRONT_RIGHT_LIFT() setServoAngle(2, 0)
#define FRONT_RIGHT_LOWER() setServoAngle(2, 90)
#define FRONT_RIGHT_HIP(n) setServoAngle(3, n)

#define REAR_RIGHT_LIFT() setServoAngle(4, 180)
#define REAR_RIGHT_LOWER() setServoAngle(4, 90)
#define REAR_RIGHT_HIP(n) setServoAngle(5, n)

#define REAR_LEFT_LIFT() setServoAngle(6, 0)
#define REAR_LEFT_LOWER() setServoAngle(6, 90)
#define REAR_LEFT_HIP(n) setServoAngle(7, n)

void initLegs(void);

void stand(void);

void moveForward(void);
void moveBackward(void);
void moveLeft(void);
void moveRight(void);

#endif