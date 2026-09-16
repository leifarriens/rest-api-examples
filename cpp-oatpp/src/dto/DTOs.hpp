#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/macro/codegen.hpp"

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Message Data-Transfer-Object
 */
class MessageDto : public oatpp::DTO
{

  DTO_INIT(MessageDto, DTO /* Extends */)

  DTO_FIELD(Int32, statusCode); // Status code field
  DTO_FIELD(String, message);   // Message field
};

/**
 * User Data-Transfer-Object
 */
class UserDto : public oatpp::DTO
{

  DTO_INIT(UserDto, DTO /* Extends */)

  DTO_FIELD(Int64, id);    // ID field
  DTO_FIELD(String, name); // Status code field
  DTO_FIELD(Int32, age);   // Message field
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */