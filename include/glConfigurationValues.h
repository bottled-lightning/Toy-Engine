#ifndef INCLUDE_GLCONFIGURATIONVALUES_H_
#define INCLUDE_GLCONFIGURATIONVALUES_H_

namespace boost { class any; }

class glConfigurationValues : public std::map<std::string, boost::any> {
public:
    template <typename T>
    const T &get(const std::string &key) { return boost::any_cast<T>(at(key)); }
private:
    // don't want the end user to access raw boost
    using std::map<std::string, boost::any>::operator [];
    using std::map<std::string, boost::any>::at;
};

#endif
