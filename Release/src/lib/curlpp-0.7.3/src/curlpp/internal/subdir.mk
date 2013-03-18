################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/lib/curlpp-0.7.3/src/curlpp/internal/CurlHandle.o \
../src/lib/curlpp-0.7.3/src/curlpp/internal/OptionList.o \
../src/lib/curlpp-0.7.3/src/curlpp/internal/OptionSetter.o \
../src/lib/curlpp-0.7.3/src/curlpp/internal/SList.o 

CPP_SRCS += \
../src/lib/curlpp-0.7.3/src/curlpp/internal/CurlHandle.cpp \
../src/lib/curlpp-0.7.3/src/curlpp/internal/OptionList.cpp \
../src/lib/curlpp-0.7.3/src/curlpp/internal/OptionSetter.cpp \
../src/lib/curlpp-0.7.3/src/curlpp/internal/SList.cpp 

OBJS += \
./src/lib/curlpp-0.7.3/src/curlpp/internal/CurlHandle.o \
./src/lib/curlpp-0.7.3/src/curlpp/internal/OptionList.o \
./src/lib/curlpp-0.7.3/src/curlpp/internal/OptionSetter.o \
./src/lib/curlpp-0.7.3/src/curlpp/internal/SList.o 

CPP_DEPS += \
./src/lib/curlpp-0.7.3/src/curlpp/internal/CurlHandle.d \
./src/lib/curlpp-0.7.3/src/curlpp/internal/OptionList.d \
./src/lib/curlpp-0.7.3/src/curlpp/internal/OptionSetter.d \
./src/lib/curlpp-0.7.3/src/curlpp/internal/SList.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/curlpp-0.7.3/src/curlpp/internal/%.o: ../src/lib/curlpp-0.7.3/src/curlpp/internal/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -g -O0 -I/usr/include/gtkmm-2.4 -I/usr/lib/i386-linux-gnu/gtkmm-2.4/include -I/usr/include/atkmm-1.6 -I/usr/include/giomm-2.4 -I/usr/lib/i386-linux-gnu/giomm-2.4/include -I/usr/include/pangomm-1.4 -I/usr/lib/i386-linux-gnu/pangomm-1.4/include -I/usr/include/gtk-2.0 -I/usr/include/gtk-unix-print-2.0 -I/usr/include/gdkmm-2.4 -I/usr/lib/i386-linux-gnu/gdkmm-2.4/include -I/usr/include/atk-1.0 -I/usr/include/glibmm-2.4 -I/usr/lib/i386-linux-gnu/glibmm-2.4/include -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/sigc++-2.0 -I/usr/lib/i386-linux-gnu/sigc++-2.0/include -I/usr/include/cairomm-1.0 -I/usr/lib/i386-linux-gnu/cairomm-1.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/lib/i386-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/curl -I/usr/local/include/curlpp -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


