#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT helloworld : public contract {
    public:
    using contract::contract;


    // 사용 코드
    // ./cleos.sh push action 컨트랙트계정 hi '["파라미터계정"]' -p 실행주체계정(권한있는계정)
    ACTION hi(name user){
        require_auth(user);
        //계정 검사 코드
            check(has_auth(user),"XXXXX");
        print("hello,",user);
    }
    private:
};