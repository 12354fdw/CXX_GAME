#pragma once

#include <vector>

namespace bingusengine {
namespace instancetree {
namespace instancetypes {

class BaseInstance {
  public:
	BaseInstance() = default;
	virtual ~BaseInstance() = 0;

	std::vector<BaseInstance *> childrens;
	BaseInstance *parent = nullptr;
};

inline BaseInstance::~BaseInstance() = default;

} // namespace instancetypes
} // namespace instancetree
} // namespace bingusengine
