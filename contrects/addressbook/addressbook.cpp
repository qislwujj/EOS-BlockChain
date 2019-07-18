#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT addressboo: public contract{
    public:
        ACTION upsert(){}
        // ACTION modify() {}
        // ACTION insert() {}
        ACTION erase() {}
    
    private:
    sturct [[eosio::table]] person {
        name user;
        std::string first_name;
        std::string last_name;
        uint32_t age;

        uint64_t primary_key() const {return user.value;}
        //부호가 없는 64비트 값을 키로 쓰는것이 규칙임.
    };
    //테이블 이름은 나중에 추가 가능(person은 테이블이름아님)

    typedef multi_index<"people"_n,person> address_index;
    //테이블 이름 "people"로 지정, address_index로 별칭 지정
};