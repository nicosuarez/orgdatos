#ifndef RESOURCE_H_
#define RESOURCE_H_

typedef unsigned int ID_type;

#define EXT_BMP ".bmp"
#define EXT_JPG ".jpg"
#define EXT_JPEG ".jpeg"
#define EXT_PNG ".png"
#define EXT_GIF ".gif"


#define CMD_QUIT "quit"
#define CMD_ADD_DIRECTORY "adddirectory"
#define CMD_REMOVE_DIRECTORY "removedirectory"
#define CMD_HELP "help"
#define CMD_ADD_FILE "addfile"
#define CMD_REMOVE_FILE "removefile"
#define CMD_GET_FILE "getfile"
#define CMD_SHOW_FILES "showfiles"
#define CMD_SHOW_DIRECTORIES "showdirectories"
#define CMD_CHANGE_PASSWORD "changepassword"

#define LBL_HIDDEN_MSG_SIZE "Cantidad total de mensajes ocultos: "
#define ADDING_FILE "Agregando... "
#define ERR_INCORRECT_FORMAT_PNG "Formato PNG incorrecto.\n"
#define ERR_CREATE_IMAGE_PNG "No se pudo almacenar los datos de la imagen.\n"
#define ERR_VALIDATE_PNG_FORMAT "El formato png produjo un error del tipo de entrada/salida.\n"
#define ERR_VALIDATE_INFO_PNG "No se pudo obtener la informacion administrativa del png.\n"
#define ERR_CREATE_PNG_STRUCT_WRITE "No se pudo crear la estructura del png para escritura\n"
#define ERR_CREATE_PNG_STRUCT_READ "No se pudo crear la estructura del png para lectura\n"

#define ERR_INSUFFICIENT_SPACE "No hay espacio suficiente para almacenar el mensaje\n"
#define ERR_IMAGE_NOT_SUPPORT "Imagen no reconocida "
#define ERR_IMAGE_WITHOUT_CAPACITY "La imagen no tiene capacidad para ocultar un mensaje"
#define ERR_COMMAND_NOT_EXIST "El commando no existe."
#define ERR_FILE_ERROR "Error al leer en el directorio: "
#define ERR_PATH_NOT_EXIST "El directorio no exite: "
#define ERR_FILE_OPEN "No se pudo abrir el archivo: "
#define ERR_FILE_DELETE "No se pudo eliminar el archivo"
#define LBL_PROMT "> "
#define LBL_PASS "Password: "
#define EMPTY " "
#define ERR_INCORRECT_PASSWORD "El password ingresado es incorrecto."
#define ERR_SAME_PASSWORD "La validacion del password es erronea."
#define ERR_NOT_SPACE "No hay espacio suficiente para ocultar el mensaje\n"
#define ERR_ALREADY_EXIST "El mensaje que se desea ocultar ya existe\n"
#define ERR_MSG_NOT_EXIST "No existe el mensaje\n"
#define ERR_MSG_EMPTY "No hay ningun mensaje oculto\n"
#define ERR_MSG_IS_IMG "Esta intentando ocultar una imagen que fue agregada al sistema para ocultar mensajes\n" 
#define MSG_HIDE_SUCCESS "El mensaje se ha ocultado exitosamente\n\n"
#define MSG_EXTARCT_SUCCESS "El mensaje se ha extraido exitosamente\n\n"
#define MSG_DELETE_SUCCESS "El mensaje se ha eliminado correctamente\n\n"
#define MSG_NOT_EXIST_DIRECTORIES "No se agrego ningun directorio.\n"
#define MSG_NOT_MSG "No se pudo abrir el archivo.\n"
#define PROCESS_COMMAND "Procesando comando...\n"
#define MSG_INPUT_PASSWORD "\nPor favor ingrese su password."
#define MSG_CREATE_PASSWORD "\nPor favor ingrese su nuevo password."
#define MSG_COMFIRM_PASSWORD "\nPor favor confirme su password."
#define MSG_ADDED_DIRECTORIES "Los siguientes archivos han sido dado de alta\n"
#define MSG_DELETED_DIRECTORIES "Los siguientes archivos han sido eliminados\n"
#define MSG_INITIAL_PROGRAM "\n\
//////////////////////////////////////////////////////////////////////\n\
//                    Bienvenido a DataSafe v1.0                    //\n\
//////////////////////////////////////////////////////////////////////\n\
\nIngrese un comando: (Para la ayuda ingrese: help)\n"
#define ERR_PARAMS_SIZE_INCORRECT "\
La cantidad de parametros es incorrecta.\n\
Por favor respete la siguiente sintaxis para el comando:\n"

#define MSG_INTRUDERS1 "Han sido detectado que "
#define MSG_INTRUDERS2 " intruso intento entrar: \n "
#define MSG_INTRUDERS3 " intrusos intentaron entrar: \n "
#define MSG_INTRUDERS_GETPASS "Los siguientes son los passwords introduciodos por el intruso: \n "


#define HLP_HELP "\
	●   help \n \t \
	Lista la ayuda para todos los comandos disponibles."

#define HLP_QUIT "\
	●   quit \n \t Sale de la consola."

#define HLP_ADD_DIRECTORY "\
	●   addDirectory <directorio> \n \t \
	Agrega un directorio de imágenes al ocultador."

#define HLP_REMOVE_DIRECTORY "\
	●   removeDirectory <directorio> \n \t \
	Quita un directorio de imágenes del ocultador."

#define FIRST_MSG_REMOVE_DIRECTORY "Los siguientes Directorios han sido eliminados exitosamente."

#define ERR_MSG_REMOVE_DIRECTORY "El directorio que quiere borrar no existe."

#define FIRST_MSG_ADD_DIRECTORY "\nLos siguientes Directorios han sido dados de alta exitosamente:"
#define WRONG_MSG_ADD_DIRECTORY "\nEl directorio ha sido agregado previamente a la base de datos"

#define HLP_ADD_FILE "\
	●   addFile <nombre_archivo> \n \t \
	Oculta un archivo de texto en el ocultador."

#define HLP_REMOVE_FILE "\
	●   removeFile <nombre_archivo> \n \t \
	Quita un archivo de texto del ocultador."

#define HLP_GET_FILE "\
	●   getFile <nombre_archivo> <ruta_destino> \n \t \
	Obtiene un archivo del ocultador."

#define HLP_SHOW_FILES "\
	●   showFiles \n \t \
	Muestra el nombre de los archivos ocultos."

#define HLP_SHOW_DIRECTORIES "\
	●   showDirectories \n \t \
	Muestra la ruta de los directorios que contienen\n\
	que se utilizan para ocultar textos."

#define HLP_CHANGE_PASSWORD "\
	●   changePassword <old_password> <new_password> \n \t \
	Modifica el password de ingreso."

#define MSGCORRUPT_PASS "Password corrupta"

#define CHANGE_PASS_ACCEPTED "La password ha sido modificada correctamente"

#define CHANGE_PASS_WRONG_PASS "la password vieja no es correcta"

#define CIRCLE "\
	●   "

#define EXC_EFILE "Hubo un error, el usuario borro el siguiente archivo "


#endif /*RESOURCE_H_*/
