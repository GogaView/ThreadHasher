#pragma once

#include <exception>
#include <string>

class hasher_exception : public std::exception
{
public:
    explicit hasher_exception(const std::string& strMsg)
        : m_strMsg(strMsg)
    {
    }

    const char* what () const throw ()
    {
        return m_strMsg.c_str();
    }

private:
    const std::string m_strMsg;
};