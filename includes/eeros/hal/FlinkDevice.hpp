#ifndef ORG_EEROS_HAL_FLINKDEVICE_HPP_
#define ORG_EEROS_HAL_FLINKDEVICE_HPP_

#include <string>
#include <flinklib.h>

namespace eeros {
	namespace hal {

		class FlinkDevice {
		public:
			FlinkDevice(std::string deviceNode);
			virtual ~FlinkDevice();
			
			flink_dev* getDeviceHandle();

		private:
			flink_dev *it;
		};
	};
};

#endif /* ORG_EEROS_HAL_FLINKDEVICE_HPP_ */
