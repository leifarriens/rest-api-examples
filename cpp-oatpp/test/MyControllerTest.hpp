#ifndef MyControllerTest_hpp
#define MyControllerTest_hpp

#include <chrono>
#include <memory>
#include <thread>

#include "controller/MyController.hpp"
#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"

#include "oatpp-test/UnitTest.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/macro/component.hpp"

class MyControllerTest : public oatpp::test::UnitTest {
public:
  MyControllerTest() : UnitTest("MyControllerTest") {}
  void onRun() override;
};

inline void MyControllerTest::onRun() {
  TestComponent component;
  oatpp::test::web::ClientServerTestRunner runner;
  runner.addController(std::make_shared<MyController>());

  runner.run([&runner] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

    auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);
    auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);
    auto response = client->getHello();

    OATPP_ASSERT(response->getStatusCode() == 200);
    auto message = response->readBodyToDto<oatpp::Object<MessageDto>>(objectMapper.get());
    OATPP_ASSERT(message);
    OATPP_ASSERT(message->statusCode == 200);
    OATPP_ASSERT(message->message == "Hello World!");

    auto userResponse = client->getUser(42);
    OATPP_ASSERT(userResponse->getStatusCode() == 200);

    auto user = userResponse->readBodyToDto<oatpp::Object<UserDto>>(objectMapper.get());
    OATPP_ASSERT(user);
    OATPP_ASSERT(user->id == 42);
    OATPP_ASSERT(user->name == "Ada Lovelace");
    OATPP_ASSERT(user->age == 30);
  }, std::chrono::minutes(10));

  std::this_thread::sleep_for(std::chrono::seconds(1));
}

#endif
