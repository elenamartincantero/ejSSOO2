#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <future>


class Request;
class Client;
class Calculator;

std::vector <Request> v_requests;
std::condition_variable cv;
std::mutex sem;
std::unique_lock<std::mutex> ul (sem);


class Request{
    public:
        int x;
        std::promise <int> prom ;
        std::future <int> fut;

        Request(int x){
            this-> x = x;
            this -> fut = prom.get_future();
        }

};
class Client{
  
    public:
        void operator()(){
            int x;
            std::cout << "Introduzca un entero: ";
            std::cin >> x;
            Request r(x);
            v_requests.push_back(std::move(r));
            cv.notify_one();
            int factorial = v_requests.back().fut.get();
            std::cout << "Factorial = " << factorial << std::endl;
        }
};

class Calculator{

    public:
        void operator()(){
          
            cv.wait(ul, []{return !v_requests.empty();});
            int factorial = 1;
            int x = v_requests.back().x;
            std::promise <int> prom = std::move(v_requests.back().prom);
            
            for (int i = 1; i <= x; i++)
            {
                factorial *= i;
            }
            prom.set_value(factorial);
            v_requests.pop_back();
            
            
            
        }
};



int main(){
    Client cli;
    Calculator calc;
    std::thread cliente_th(cli);
    std::thread calc_th(calc);

    cliente_th.join();
    calc_th.join();
    

}