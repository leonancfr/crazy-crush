/* Universidade Federal do Rio de Janeiro
 * Escola Politécnica
 * Departamento de Eletrônica e Computação
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programação
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan França    (leonancfr@poli.ufrj.br)
 *          Gustavo Silva    (diguser@gmail.com)
 *          Michael Douglas  (michaeldouglas@poli.ufrj.br)
 */
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_ 1

//! Classe que cria e manipula um arquivo de LOG em formato HTML
class Logger {
  private:
    void* output;
  public:
    //! Tipos de mensagens possíveis
    enum { error,warning,log,debug,info };
    
    //! Instacia a classe já passando o nome do arquivo de saída
    /**
    \param filename: Nome do arquivo de saída do log
    */
    Logger(const char* filename);
    
    ~Logger();
    
    //! Envia a mensagem para o arquivo de log
    /**
    Recomenda-se o uso de uma das seguintes macros:
    LOG_LOG(""); LOG_DEBUG(""); LOG_ERROR(""); LOG_WARN(""); LOG_INFO("");
    
    \param filename: Nome do arquivo atual
    \param line: Número da linha atual
    \param message: Mensagem a ser salva no log
    \param type: Tipo da mensagem de log
    */
    void msg(const char* filename, const unsigned line, const char* message, const char type= debug);
};

extern Logger console;

#define LOG_LOG(a) console.msg(__FILE__,__LINE__, a ,Logger::log)
#define LOG_DEBUG(a) console.msg(__FILE__,__LINE__, a ,Logger::debug)
#define LOG_ERROR(a) console.msg(__FILE__,__LINE__, a ,Logger::error)
#define LOG_WARN(a) console.msg(__FILE__,__LINE__, a ,Logger::warning)
#define LOG_WARNING(a) console.msg(__FILE__,__LINE__, a ,Logger::warning)
#define LOG_INFO(a) console.msg(__FILE__,__LINE__, a ,Logger::info)

#endif