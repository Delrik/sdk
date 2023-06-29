#pragma once

#include <memory>

class NavAppImpl;

class NavApp {
 private:
  std::shared_ptr<NavAppImpl> m_pimpl;
};