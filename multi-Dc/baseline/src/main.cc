#include"client.h"
#include"gateway.h"
#include"server.h"
#include"common.h"
#include<fstream>
using namespace std;

vector<Server> serverArr;

Client client;
Gateway gateWay;

bool init();
bool loadBalanceAna();

int main(int argc, char* argv[])
{
    init();

    client.setTestOp(argv[2]);
//    gateWay.testConsHash();

    ifstream file(argv[1], ios::in);
    string message;

    while(!file.eof()){
	getline(file, message);
	if(!message.compare(""))
	    continue;
//	fprintf(stderr, "%s\n", message.c_str());
	client.sendMessage(message);
//	fprintf(stderr, "\n");
    }

    fprintf(stdout, "%s\n", argv[2]);
    string op(argv[2]);
    if(!op.compare("write"))
	loadBalanceAna();

    client.getStat();
}

bool init()
{
    uint16_t cnt = 0;
    for(int i = 0 ; i < dcNum ; i++){
	for(int j = 0; j < (1 << serverPerDcBit); j++){
	    if(j < datacenter[i]){
		Server s(cnt, true, defaultCapacity);
		serverArr.push_back(s);
	    }
	    else{
		Server s(cnt, false, defaultCapacity);
		serverArr.push_back(s);
	    }
	    cnt++;
	}
    }

    //init gateway
    gateWay.setting(&serverArr);
    //init client
    client.setGateWay(&gateWay);

    fprintf(stdout, "== system overview ==\n");
    for(int i = 0 ; i < dcNum ; i++)
	fprintf(stdout, "Data Center %d:\t%d\n", i, datacenter[i]);
    fprintf(stdout, "== END ==\n");
}

bool loadBalanceAna()
{
    uint64_t max = 0;
    uint64_t min = defaultCapacity;
    uint16_t cnt1 = 0;
    uint16_t cnt2 = 0;
    uint16_t cnt3 = 0;
    uint16_t cnt4 = 0;
    uint16_t cnt5 = 0;
    for(vector<Server>::iterator iter = serverArr.begin(); iter != serverArr.end(); iter++)
    {
	if(iter->getState()){
	    if(iter->getUsedCapacity() < 1000000000)
		cnt1++;
	    else if(iter->getUsedCapacity() < 10000000000)
		cnt2++;
	    else if(iter->getUsedCapacity() < 50000000000)
		cnt3++;
	    else if(iter->getUsedCapacity() < 100000000000)
		cnt4++;
	    else
		cnt5++;
	    if(iter->getUsedCapacity() > max)
		max = iter->getUsedCapacity();
	    if(iter->getUsedCapacity() < min)
		min = iter->getUsedCapacity();
	    fprintf(stdout, "server number: %u\tused storage: %lu  \tfile number: %lu, \n", iter->getNum(), iter->getUsedCapacity(), iter->getFileNum());
	}
    }
    fprintf(stdout, "usedstorage: <1G:\t%u\n", cnt1);
    fprintf(stdout, "usedstorage: 1G ~ 10G:\t%u\n", cnt2);
    fprintf(stdout, "usedstorage: 10G ~ 50G:\t%u\n", cnt3);
    fprintf(stdout, "usedstorage: 50G ~ 100G:\t%u\n", cnt4);
    fprintf(stdout, "usedstorage: >100G:\t%u\n", cnt5);

    fprintf(stdout, "max:\t%lu\n", max);
    fprintf(stdout, "min:\t%lu\n", min);
}