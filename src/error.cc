#include <sstream>
#include "error.hh"

namespace srpg::err {


NoSuchFileError::NoSuchFileError(const std::string& file) {
  std::stringstream msg;
  msg << "Unable to find file: " << file;

  what(msg.str());
}

GenericError::GenericError(std::string what) {
  what_ = std::move(what);
}

const char* GenericError::what() const noexcept {
  return what_.c_str();
}

void GenericError::what(std::string what) {
  what_ = std::move(what);
}

}  // namespace srpg::err