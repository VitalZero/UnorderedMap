#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <iostream>

// "window messages"
#define WM_CREATE 0
#define WM_PAINT 1
#define WM_DEFAULT -1

// suppose std::function takes the 4 arguments from wndproc and the return value is LRESULT instead of int
using MapFunction = std::function<int(int,int)>;
using MsgMap = std::unordered_map<int, MapFunction>;

// Link the functions to the messages
void Register(int msg, MsgMap& map, MapFunction func);

int OnPaint(int param1, int param2)
{
  std::cout << "I'm paint!, params: " << param1 << ", " << param2 << " ->";

  return param1 + param2;
}
int OnCreate(int param1, int param2)
{
  std::cout << "I'm create!, params: " << param1 << ", " << param2 << " ->";

  return param1 * param2;
}
int OnDefault(int param1, int param2)
{
  std::cout << "THE DEFAULT, params: " << param1 << ", " << param2 << " ->";

  return param1 + param1 * param2 + param2;
}

int main()
{
  MsgMap map;

  Register(WM_CREATE, map, OnCreate);
  Register(WM_PAINT, map, OnPaint);
  // add a default function in case of unhandled msg
  Register(WM_DEFAULT, map, OnDefault);

  srand(time(nullptr));

  for(int i = 0; i < 10; ++i)
  {
    int nMsg = rand() % 10;
    std::cout << "#" << i << ".- Message: " << nMsg << " is: ";

    auto itr = map.find(nMsg);
    if(itr != map.end())
    {
      std::cout << "returned: " << itr->second(1, 2) << std::endl;
    }
    else
    {
      std::cout << "returned: " << map[WM_DEFAULT](2, 2) << std::endl;
    }
  }

  return 0;
}

void Register(int msg, MsgMap& map, MapFunction func)
{
  if(map.find(msg) == map.end())
  {
    map[msg] = func;
  }
}