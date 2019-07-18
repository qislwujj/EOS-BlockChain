// ssh root@183.102.228.122 -p 1027
// qortjr1234
// cd /home/ibct/baekseok/eosio-biosboot


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

    // // 컨트랙트 배포자만 사용할수 있게
    // name mkuser = get_self();
    // // name mkuser = name("ibctibct1234");
    // ACTION hi(name user){  
    //         check(has_auth(mkuser),"xxxxx");
    //         // require_auth( get_self() );
    //     print("hello,",user);
    // }



    // 지정한 사람만 사용할 수 있게 하기
    // ACTION hi(name user){
    //     require_auth(user);
    //         check(has_auth(get_self()) || has_auth("sks123123123"_n) ,"xxxxx");
    //     print("hello,",user);
    // }




// 계정 유무 확인??
    ACTION hi(name user){
        require_auth(user);
        print("hello,",user);
    }

    ACTION getaccount(name user){
        require_auth(get_self());
        print(is_account(user));
    }






    private:
};