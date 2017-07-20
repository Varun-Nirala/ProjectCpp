#ifndef __HELPER_H__
#define __HELPER_H__

#include <iostream>
#include <string>
#include <sstream>

#define SAFE_RELEASE(x) if(x)\
                        {\
                            x->release();\
                            x = nullptr;\
                        }
                        
#define SAFE_DELETE(x)  if(x)\
                        {\
                            delete x;\
                            x = nullptr;\
                        }

#define NDEBUG

#ifdef NDEBUG
    #define LOG_INFO(msg)   std::cout << "INFO :: " << __FUNC__ << "::" << __line__ << " -> " << msg << "." << std::endl
    #define LOG_DEBUG(msg)  std::cout << "DEBUG :: " << __FUNC__ << "::" << __line__ << " -> " << msg << "." << std::endl
    #define LOG_ENTRY       std::cout << "INFO :: ENTERING -> " << __FUNC__ << " :: " << __line__ << std::endl
    #define LOG_EXIT        std::cout << "INFO :: EXITING  <- " << __FUNC__ << " :: " << __line__ << std::endl
#else
    #define LOG_INFO(msg)   ;
    #define LOG_DEBUG(msg)  ;
    #define LOG_ENTRY       ;
    #define LOG_EXIT        ;
#endif

#define LOG_ERROR(msg)  std::cout << "ERROR :: " << func << "::" << line << ":: " << error_code << " -> "<< msg << "." << std::endl

template<typename T>    // For int, char, float, double and long
T ReadInput()
{
    T rc;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    ss >> rc;
    return rc;
}
#endif