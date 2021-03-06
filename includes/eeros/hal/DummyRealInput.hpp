#ifndef ORG_EEROS_HAL_DUMMYREALINPUT_HPP_
#define ORG_EEROS_HAL_DUMMYREALINPUT_HPP_

#include <string>
#include <eeros/hal/ScalablePeripheralInput.hpp>

namespace eeros {
	namespace hal {

		class DummyRealInput : public ScalablePeripheralInput<double> {
		public:
			DummyRealInput(std::string id, double scale = 1, double offset = 0);
			virtual double get();
		};
	};
};

#endif /* ORG_EEROS_HAL_DUMMYREALINPUT_HPP_ */
