
class PIDController {

private:
  double kP;
  int minSpeed;
  int error;

public:
  int getSpeedToMotor(int target, int current);
  PIDController(double inKP, int inMinSpeed);
  double getError();
};
