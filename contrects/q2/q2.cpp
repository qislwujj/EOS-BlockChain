// <action>countuser(name user)         :본인만 해당 액션 실행 가능, 이 액션을 실행할 때마다 Table의 변수를 1씩 증가(유저마다 1개씩 보유)
// <action>findcount(uint64_t count)    :secondary index로 등록된 count찾기
// <action>eraseall()                   :table의 모든 정보 삭제(erase 함수 이용) itr++하면 이레티어 1씩 이동 가능   해당 itr을 삭제하고 다음 itr 반환
// <table> counttable                   :primary key는 user.value   , scope는 get_self().value  , 추가적으로 uint64_t count라는 변수를 갖고 있고, 이를 secondary index로 만듦
#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;


CONTRACT q2: public contract {
public:
using contract::contract;


ACTION findcount(uint64_t count){
    secondary_index fc(get_self(),get_self().value);
    auto forSecondary = fc.get_index<"bycount"_n>();
    auto itr = forSecondary.require_find(count,"no count");

    print(itr->user," ",itr->count);
}



// ACTION upsert(name user, uint64_t count) {
//     require_auth(user);
//     secondary_index forUpsert(get_self(),get_self().value);
//     auto itr = forUpsert.find(user.value);

//     if(itr == forUpsert.end()){
//         forUpsert.emplace(user, [&](auto& row) {
//             row.user = user;
//             row.count = count;
//             });
//             print("emplace success");
//     }
//     else{
//         forUpsert.modify(itr,user, [&](auto& row) {
//             row.user = user;
//             row.count = count;
//             });
//             print("modify success");
//     }

// }

ACTION countuser(name user){
    require_auth(user);
        
        secondary_index forPlus(get_self(), get_self().value);
        // auto itr = forPlus.get_index<"bycount"_n>();
            auto itr = forPlus.find(user.value);
            if(itr == forPlus.end()){
                forPlus.emplace(user, [&](auto& row) {
                    row.user = user;
                    row.count =1;
                });
            print("emplace success");
            
            } else {
                forPlus.modify(itr,user, [&](auto& row) {
                    row.user = user;
                    row.count ++;
                });
                print( itr->user,itr->count );
                print("modify success");
            }
}



ACTION eraseall() {
    // require_auth(user);

    secondary_index forErase(get_self(), get_self().value);
    // auto itr = forErase.require_find(user.value, "no account");
    for(auto itr = forErase.begin(); itr != forErase.end();){
        
        itr= forErase.erase(itr);
    }
    

    print("eraseall success");
}

private:
struct [[eosio::table]] person {
    name user;
    uint64_t count;

    uint64_t primary_key() const { return user.value; }
    uint64_t by_count() const{return count; }
};

typedef multi_index<"counttable"_n, person,
indexed_by<"bycount"_n,const_mem_fun<person,uint64_t,&person::by_count>> > secondary_index;
};