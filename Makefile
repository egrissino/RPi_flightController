# You need to "sudo apt-get install libgtkmm-3.0-dev" to build the demo_3d binary

all: flightController

HDRS = helper_3dmath.h I2Cdev.h MPU6050_6Axis_MotionApps20.h MPU6050.h demo_3d.h PID.h
CMN_OBJS = I2Cdev.o MPU6050.o
DMP_OBJS = flightController.o

CXXFLAGS = -DDMP_FIFO_RATE=9 -Wall -std=c++11 -lwiringPi -lpthread -g -O2 `pkg-config gtkmm-3.0 --cflags --libs`

$(CMN_OBJS) $(DMP_OBJS) : $(HDRS)

flightController: $(CMN_OBJS) $(DMP_OBJS) $(WPI_OBJS)
	$(CXX) -lpthread -lwiringPi -o $@ $^ -lm

clean:
	rm -f $(CMN_OBJS) $(DMP_OBJS) $(D3D_OBJS) $(RAW_OBJS) flightController

