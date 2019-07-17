#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT helloworld : public contract {
    public:
    using contract::contract;


    // 사용 코드
    // ./cleos.sh push action 컨트랙트계정 hi '["파라미터계정"]' -p 실행주체계정(권한있는계정)

    // ACTION hi(name user){
    //     // require_auth(user);
    //     //계정 검사 코드
    //         check(has_auth(user),"xxxxx");
    //     print("hello,",user);
    // }

    // 컨트랙트 배포자만 사용할수 있게
    name mkuser = get_self();
    // name mkuser = name("ibctibct1234");
    ACTION hi(name user){
        
            check(has_auth(mkuser),"xxxxx");
        print("hello,",user);
    }
    private:
};