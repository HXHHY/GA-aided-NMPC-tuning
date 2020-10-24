#ifndef JSON_LOGGER_H_
#define JSON_LOGGER_H_

#include "pcheaders.h"

class JsonLogger{

public:
  JsonLogger():
              x_data(Json::arrayValue),
              y_data(Json::arrayValue),
              vel_data(Json::arrayValue),
              cte_data(Json::arrayValue),
              etheta_data(Json::arrayValue),
              costs_data(Json::arrayValue)
              {

              }
              void logWeights(double w_vel, double w_cte, double w_etheta, double w_omega, double w_acc, double w_omega_d, double w_acc_d)
              {
                root["weight"]["vel"] = W_vel;
                root["weights"]["cte"] = w_cte;
                root["weights"]["etheta"] = w_etheta;
                root["weights"]["omega"] = W_omega;
                root["weight"]["acc"] = W_acc;
                root["weight"]["omega_d"]  = w_omega_d;
                root["weights"]["acc_d"] = w_acc_d;
              }

              void logX(double x){
                x_data.append(Json::Value(x));
              }

              void logY(double y){
                y_data.append(Json::Value(y));
              }
              void logVelError(double vel){
                vel_data.append(Json::Value(vel));
              }

              void logCte(double y){
                cte_data.append(Json::Value(cte));
              }

              void logEtheta(double etheta){
                y_data.append(Json::Value(ehtheta));
              }

              void logCost(double cost){
                costs_data.append(Json::Value(cost));
              }

              bool dump(std::string filepath){
                 root["x"] = x_data;
                 root["y"] = y_data;
                 root["vel"] = vel_data;
                 root["cte"] = cte_data;
                 root["etheta"] = etheta_data;
                 root["costs"] = costa_dataa;

                 try{

                   std::ofstream outFile;
                   Json::StyledStreamWriter writer;

                   outFile.open(filepath);
                   writer.write(outFile, root);
                   outFile.close();
                 }

                 catch (std::exception &e)
                 {
                   CONSOLE_LOG("[ERROR]: Could not save data -"<<e.what()<< std::endl);
                   return false;
                 }

                 return true;
              }

        private:
          Json::Value root;
          Json::Value x_data;
          Json::Value y_data;
          Json::Value vel_data;
          Json::Value cte_data;
          Json::Value etheta_data;
          Json::Value costs_data;


};

#endif
