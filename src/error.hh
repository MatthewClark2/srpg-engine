#ifndef SRPG_ENGINE_ERROR_HH
#define SRPG_ENGINE_ERROR_HH

#include <string>

namespace srpg::err {

class GenericError : public std::exception {
 public:
  explicit GenericError(std::string what = "");

  const char* what() const noexcept override;

  void what(std::string what);

 private:
  std::string what_;
};

class NoSuchFileError : public GenericError {
 public:
  explicit NoSuchFileError(const std::string& file);
};

} // namespace srpg::err

#endif //SRPG_ENGINE_ERROR_HH
