/*
 * svr_user.h
 *
 *  Created on: 16/01/2014
 *      Author: jarico
 */

#ifndef SVR_USER_H_
#define SVR_USER_H_

#include "svr_util.h"

class SVR_user {

private:

	char  Id        [FIELD_LEN];
	char  Nombre    [FIELD_LEN];
	char  Apellidos [FIELD_LEN];
	char  Bio       [FIELD_LEN];
	char  Email     [FIELD_LEN];

public:

	 SVR_user();
	 SVR_user(char *id, char *nombre, char *apellidos, char *bio, char *email);

	 void  ponerId        (const char *id);
	 void  ponerNombre    (const char *nombre);
	 void  ponerApellidos (const char *apellidos);
	 void  ponerBio       (const char *bio);
	 void  ponerEmail     (const char *email);

	 char *obtenerId        ();
	 char *obtenerNombre    ();
	 char *obtenerApellidos ();
	 char *obtenerBio       ();
	 char *obtenerEmail     ();

	 int   obtenerIdLen        ();
	 int   obtenerNombreLen    ();
	 int   obtenerApellidosLen ();
	 int   obtenerBioLen       ();
	 int   obtenerEmailLen     ();

	 void  mostrar ();

	 bool  operator == (const SVR_user &user);

	~SVR_user();
};

#endif /* SVR_USER_H_ */
