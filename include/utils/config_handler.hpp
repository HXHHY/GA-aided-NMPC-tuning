#ifndef MPC_CONFIG_PARSER_H_
#define MPC_CONFIG_PARSER_H_

#include "pcheaders.h"

//Runtime configurations
namespace config
{

    enum ConfigType
    {
        GA,
        MONO
    };


    struct GeneticAlgorithm
    {
        struct General
        {
            size_t generations, population_size, mating_pool_size, iterations_per_genome;
        } general;

        struct Operators
        {
            double mutation_probability, crossover_bias;
        } operators;
    };

    struct MPC_Controller_GA
    {
        struct __General
        {
            size_t timesteps;
            double sample_time;

        } general;

        struct __Desired
        {
            double velocity, cross_track_error, orientation_error;
        } desired;

        struct __MaxBounds
        {
            double omega, throttle;
        } max_bounds;

        struct __WeightBounds
        {
            std::pair<double, double> w_cte, w_etheta, w_vel, w_omega, w_acc, w_omega_d, w_acc_d;
        } weight_bounds;
    };


    struct MPC_Controller_MONO
    {
        struct __General
        {
            size_t timesteps;
            double sample_time;

        } general;

        struct __Desired
        {
            double velocity, cross_track_error, orientation_error;
        } desired;

        struct __MaxBounds
        {
            double omega, throttle;
        } max_bounds;

        struct __Weights
        {
            double w_cte, w_etheta, w_vel, w_omega, w_acc, w_omega_d, w_acc_d;
        } weights;

        struct __TeardownTolerance
        {
            double velocity, cross_track_error, orientation_error;
        } teardown_tolerance;
    };

    template <ConfigType ctype>
    class ConfigHandler
    {

    public:
        ConfigHandler(const ConfigHandler &) = delete;

        static YAML::Node Root()
        {
            return get().RootImpl();
        }

        template <ConfigType U = ctype>
        typename std::enable_if<U == 0, GeneticAlgorithm &>::type static getGAConfig()
        {
            return get().getGAConfigImpl();
        }


        template <ConfigType U = ctype>
        typename std::enable_if<U == 0, MPC_Controller_GA &>::type static getMpcConfig()
        {
            return get().getMpcConfigImpl();
        }


        template <ConfigType U = ctype>
        typename std::enable_if<U == 1, MPC_Controller_MONO &>::type static getMpcConfig()
        {
            return get().getMpcConfigImpl();
        }

    private:
        /// Name of file to parse
        std::string m_filename;
        YAML::Node m_root;
        MPC_Controller_GA m_mpcConfigGA;
        MPC_Controller_MONO m_mpcConfigMono;
        GeneticAlgorithm m_genConfig;


        ConfigHandler()
        {
            switch (ctype)
            {
            case GA:
                m_filename = "config/config-ga.yaml";
                break;

            case MONO:
                m_filename = "config/config-mono.yaml";
                break;

            default:
                break;
            }

            m_root = YAML::LoadFile(m_filename);

            _updateInternalData();
        }


        void _updateInternalData()
        {
            DEBUG_LOG("Parsing configuration files ...");
            switch (ctype)
            {
            case GA:
            {
                m_genConfig.general.generations = m_root["Genetic-Algorithm"]["General"]["generations"].as<size_t>();
                m_genConfig.general.population_size = m_root["Genetic-Algorithm"]["General"]["population_size"].as<size_t>();
                m_genConfig.general.mating_pool_size = m_root["Genetic-Algorithm"]["General"]["mating_pool_size"].as<size_t>();
                m_genConfig.general.iterations_per_genome = m_root["Genetic-Algorithm"]["General"]["iterations_per_genome"].as<size_t>();

                m_genConfig.operators.mutation_probability = m_root["Genetic-Algorithm"]["Operators"]["mutation_probability"].as<double>();
                m_genConfig.operators.crossover_bias = m_root["Genetic-Algorithm"]["Operators"]["crossover_bias"].as<double>();

                m_mpcConfigGA.general.timesteps = m_root["MPC-Controller"]["General"]["timesteps"].as<size_t>();
                m_mpcConfigGA.general.sample_time = m_root["MPC-Controller"]["General"]["sample_time"].as<double>();

                m_mpcConfigGA.desired.velocity = m_root["MPC-Controller"]["Desired"]["velocity"].as<double>();
                m_mpcConfigGA.desired.cross_track_error = m_root["MPC-Controller"]["Desired"]["cross_track_error"].as<double>();
                m_mpcConfigGA.desired.orientation_error = m_root["MPC-Controller"]["Desired"]["orientation_error"].as<double>();

                m_mpcConfigGA.max_bounds.omega = m_root["MPC-Controller"]["Max-Bounds"]["omega"].as<double>();
                m_mpcConfigGA.max_bounds.throttle = m_root["MPC-Controller"]["Max-Bounds"]["throttle"].as<double>();

                YAML::Node bounds = m_root["MPC-Controller"]["Weight-Bounds"];

                m_mpcConfigGA.weight_bounds.w_cte = std::make_pair(bounds["w_cte"][0].as<double>(), bounds["w_cte"][1].as<double>());
                m_mpcConfigGA.weight_bounds.w_etheta = std::make_pair(bounds["w_etheta"][0].as<double>(), bounds["w_etheta"][1].as<double>());
                m_mpcConfigGA.weight_bounds.w_vel = std::make_pair(bounds["w_vel"][0].as<double>(), bounds["w_vel"][1].as<double>());
                m_mpcConfigGA.weight_bounds.w_omega = std::make_pair(bounds["w_omega"][0].as<double>(), bounds["w_omega"][1].as<double>());
                m_mpcConfigGA.weight_bounds.w_acc = std::make_pair(bounds["w_acc"][0].as<double>(), bounds["w_acc"][1].as<double>());
                m_mpcConfigGA.weight_bounds.w_omega_d = std::make_pair(bounds["w_omega_d"][0].as<double>(), bounds["w_omega_d"][1].as<double>());
                m_mpcConfigGA.weight_bounds.w_acc_d = std::make_pair(bounds["w_acc_d"][0].as<double>(), bounds["w_acc_d"][1].as<double>());
                break;
            }
            case MONO:
            {
                m_mpcConfigMono.general.timesteps = m_root["MPC-Controller"]["General"]["timesteps"].as<size_t>();
                m_mpcConfigMono.general.sample_time = m_root["MPC-Controller"]["General"]["sample_time"].as<double>();

                m_mpcConfigMono.desired.velocity = m_root["MPC-Controller"]["Desired"]["velocity"].as<double>();
                m_mpcConfigMono.desired.cross_track_error = m_root["MPC-Controller"]["Desired"]["cross_track_error"].as<double>();
                m_mpcConfigMono.desired.orientation_error = m_root["MPC-Controller"]["Desired"]["orientation_error"].as<double>();

                m_mpcConfigMono.max_bounds.omega = m_root["MPC-Controller"]["Max-Bounds"]["omega"].as<double>();
                m_mpcConfigMono.max_bounds.throttle = m_root["MPC-Controller"]["Max-Bounds"]["throttle"].as<double>();

                m_mpcConfigMono.weights.w_cte = m_root["MPC-Controller"]["Weights"]["w_cte"].as<double>();
                m_mpcConfigMono.weights.w_etheta = m_root["MPC-Controller"]["Weights"]["w_etheta"].as<double>();
                m_mpcConfigMono.weights.w_vel = m_root["MPC-Controller"]["Weights"]["w_vel"].as<double>();
                m_mpcConfigMono.weights.w_omega = m_root["MPC-Controller"]["Weights"]["w_omega"].as<double>();
                m_mpcConfigMono.weights.w_acc = m_root["MPC-Controller"]["Weights"]["w_acc"].as<double>();
                m_mpcConfigMono.weights.w_omega_d = m_root["MPC-Controller"]["Weights"]["w_omega_d"].as<double>();
                m_mpcConfigMono.weights.w_acc_d = m_root["MPC-Controller"]["Weights"]["w_acc_d"].as<double>();

                m_mpcConfigMono.teardown_tolerance.velocity = m_root["MPC-Controller"]["Teardown-Tolerance"]["velocity"].as<double>();
                m_mpcConfigMono.teardown_tolerance.cross_track_error = m_root["MPC-Controller"]["Teardown-Tolerance"]["cross_track_error"].as<double>();
                m_mpcConfigMono.teardown_tolerance.orientation_error = m_root["MPC-Controller"]["Teardown-Tolerance"]["orientation_error"].as<double>();
                break;
            }
            default:
                break;
            }
        }


        static ConfigHandler &get()
        {
            static ConfigHandler s_Instance;
            return s_Instance;
        }

        /************************* IMPLEMENTATIONS *************************/

        YAML::Node RootImpl()
        {
            return m_root;
        }

        template <ConfigType U = ctype>
        typename std::enable_if<U == 0, GeneticAlgorithm &>::type getGAConfigImpl()
        {
            return m_genConfig;
        }

        template <ConfigType U = ctype>
        typename std::enable_if<U == 0, MPC_Controller_GA &>::type getMpcConfigImpl()
        {
            return m_mpcConfigGA;
        }

        template <ConfigType U = ctype>
        typename std::enable_if<U == 1, MPC_Controller_MONO &>::type getMpcConfigImpl()
        {
            return m_mpcConfigMono;
        }
    };
}

#endif
