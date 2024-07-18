// 小彭老师作业05：假装是多线程 HTTP 服务器 - 富连网大厂面试官觉得很赞
#include <functional>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <future>
#include "thread_pool.h"
//struct User {
//    std::string password;
//    std::string school;
//    std::string phone;
//};
//std::shared_mutex user_mt;
//std::shared_mutex log_mt;
//std::map<std::string, User> users;
//std::map<std::string, std::chrono::steady_clock::time_point> has_login;  // 换成 std::chrono::seconds 之类的
//
//// 作业要求1：把这些函数变成多线程安全的
//// 提示：能正确利用 shared_mutex 加分，用 lock_guard 系列加分
//std::string do_register(std::string username, std::string password, std::string school, std::string phone) {
//	std::lock_guard grd(user_mt);
//    User user = {password, school, phone};
//    if (users.emplace(username, user).second)
//        return "注册成功";
//    else
//        return "用户名已被注册";
//}
//
//std::string do_login(std::string username, std::string password) {
//    // 作业要求2：把这个登录计时器改成基于 chrono 的
//	std::unique_lock ulg(log_mt);
//	auto now = std::chrono::steady_clock::now();
//    if (has_login.find(username) != has_login.end()) {
//        auto sec = now - has_login.at(username);  // C++语言算时间差
//		int64_t ms = std::chrono::duration_cast<std::chrono::seconds>(sec).count();
//        return std::to_string(ms) + "秒内登录过";
//    }
//    has_login[username] = now;
//	ulg.unlock();
//	std::shared_lock shr(user_mt);
//    if (users.find(username) == users.end())
//        return "用户名错误";
//    if (users.at(username).password != password)
//        return "密码错误";
//    return "登录成功";
//}
//
//std::string do_queryuser(std::string username) {
//	std::shared_lock slg(user_mt);
//    auto &user = users.at(username);
//    std::stringstream ss;
//    ss << "用户名: " << username << std::endl;
//    ss << "学校:" << user.school << std::endl;
//    ss << "电话: " << user.phone << std::endl;
//    return ss.str();
//}
//
//
//
//struct ThreadPool {
//	std::vector<std::future<void>> fts;
//	void create(std::function<void()> start) {
//		// 作业要求3：如何让这个线程保持在后台执行不要退出？
//		// 提示：改成 async 和 future 且用法正确也可以加分
////        std::thread thr(start);
//		fts.push_back(std::async(start));
//	}
//	ThreadPool()
//	{
//		for (auto& ft : fts)
//		{
//			ft.wait();
//		}
//	}
//};
//
//
//ThreadPool tpool;
//
//
//namespace test {  // 测试用例？出水用力！
//std::string username[] = {"张心欣", "王鑫磊", "彭于斌", "胡原名"};
//std::string password[] = {"hellojob", "anti-job42", "cihou233", "reCihou_!"};
//std::string school[] = {"九百八十五大鞋", "浙江大鞋", "剑桥大鞋", "麻绳理工鞋院"};
//std::string phone[] = {"110", "119", "120", "12315"};
//}

void printMessage(const string& message) {
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟任务的处理时间
	cout << message << endl;
}

int add(int a, int b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 模拟任务的处理时间
	return a + b;
}

int main() {
	threadPool pool(4);  // 创建一个包含4个线程的线程池

	// 提交一些任务
	auto future1 = pool.enqueue(printMessage, "Hello from thread pool!");
	auto future2 = pool.enqueue(printMessage, "Another message!");
	auto future3 = pool.enqueue(printMessage, "More messages...");
	auto future4 = pool.enqueue(printMessage, "Yet another message...");
	auto future5 = pool.enqueue(add, 1, 2);
	auto future6 = pool.enqueue(add, 3, 4);
	auto future7 = pool.enqueue(add, 5, 6);
	auto future8 = pool.enqueue(add, 7, 8);

	// 等待任务完成并获取结果
	future1.get();
	future2.get();
	future3.get();
	future4.get();
	cout << "Result of 1 + 2: " << future5.get() << endl;
	cout << "Result of 3 + 4: " << future6.get() << endl;
	cout << "Result of 5 + 6: " << future7.get() << endl;
	cout << "Result of 7 + 8: " << future8.get() << endl;

	// 线程池析构时会自动停止所有线程
	return 0;
}