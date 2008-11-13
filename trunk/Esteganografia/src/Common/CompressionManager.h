
#ifndef __COMPRESSIONMANAGER_H_
#define __COMPRESSIONMANAGER_H_

#include "Message.h"

/**
 * Clase que se encarga de la logica de compresion y descompresion de los mensajes
 * aplicando el algoritmo que corresponda.
 */
class CompressionManager
{

	static const std::string targetDescompress;
	static const std::string targetCompress;
	public:

		/*Devuelve la unica instancia de CompressionManager (clase singleton)*/
		static CompressionManager* GetInstance();

		/* Comprime el mensaje. Lanza excepcion del tipo eFile */
		static Message Compress(const Message& msg);

		/* Descomprime el mensaje.*/
		static Message Decompress(const Message& msg);

		/* Destructor */
		virtual ~CompressionManager();

	private:

		static const std::string targetDescompress;
		static const std::string targetCompress;

		/*Puntero a la unica instancia del CompressionManager*/
		static CompressionManager* instance;

		/* Constructor privado */
		CompressionManager();

		/*Constructor de copia y operador = privados para evitar errores*/
		CompressionManager(const CompressionManager &manager);
		CompressionManager& operator=(const CompressionManager &manager);

};
#endif // __COMPRESSIONMANAGER_H_
