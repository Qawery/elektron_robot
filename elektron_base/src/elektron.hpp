/*
 * protonek.hh
 *
 *  Created on: Sep 5, 2009
 *      Author: konradb3
 */

#ifndef PROTONEK_HH_
#define PROTONEK_HH_

#include <stdint.h>
#include <termios.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

#define BAUD B9600
#define PORT = "/dev/ttyUSB0"
#define WHEEL_DIAM 0.1 // in SI units [m]
#define REGULATOR_RATE 100 // in SI units [Hz]
#define AXLE_LENGTH 0.355

#define MAX_VEL 300 // in internal units
#define ENC_TICKS 4000

struct tsetvel
{
  int8_t  start;
  int8_t  cmd;
  int16_t lvel;
  int16_t rvel;
}  __attribute__((__packed__));

struct tsetpid
{
  int16_t p;
  int16_t i;
  int16_t d;
} __attribute__((__packed__));

struct tgetdata
{

  int16_t rindex;
  uint16_t rpos;

  int16_t lindex;
  uint16_t lpos;

  int16_t rvel;
  int16_t lvel;
}  __attribute__((__packed__));

class Protonek
{
public:
  Protonek(const std::string& port, int baud = BAUD);
  ~Protonek();

  void update();

  void setVelocity(double lvel, double rvel);
  void getVelocity(double &lvel, double &rvel);

  void updateOdometry();
  void getRawOdometry(double &linc, double &rinc);
  void getOdometry(double &x, double &y, double &a);
  void setOdometry(double x, double y, double a);

  bool isConnected();

  double m_per_tick;
  double robot_axle_length;
  double enc_ticks;

private:
  // serial port descriptor
  int fd;
  struct termios oldtio;
  bool connected;

  tsetvel setvel;
  tgetdata getdata;

  int llpos;
  int lrpos;

  double xpos;
  double ypos;
  double apos;

  bool odom_initialized;

};

#endif /* PROTONEK_HH_ */
