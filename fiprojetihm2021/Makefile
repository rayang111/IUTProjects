# COMMANDES #
JAVAC = javac
# note $$ to get a single shell $
JAVAC_OPTIONS = -d build -classpath build -sourcepath "src:tmp" -cp ".:./mariadb-client.jar" 
JAVA_OPTIONS = -cp ".:./mariadb-client.jar"
JAVA = java 
JAR = jar
EXEC_JAR = ${JAVA} -cp test-mnp.jar:.:./mariadb-client.jar fr.iutfbleau.projetIHM2021FI2.MNP.Booking

# CHEMINS RELATIFS
SRC = ./src/fr/iutfbleau/projetIHM2021FI2
BUILD = ./build/fr/iutfbleau/projetIHM2021FI2
DOC = ./doc/fr/iutfbleau/projetIHM2021FI2

# CHOIX NOMS
JAR_MNP = test-mnp.jar

# BUTS FACTICES #
.PHONY : run clean doc

# BUT PAR DEFAUT #
run : ${JAR_MNP}
	${EXEC_JAR} ${JAR_MNP}

# AUTRE BUTS
doc :
	javadoc -d doc -cp ".:./build:mariadb-client.jar" ./src/fr/iutfbleau/projetIHM2021FI2/API/*.java ./src/fr/iutfbleau/projetIHM2021FI2/MNP/*.java

clean :
	rm -rf ${BUILD}/* *.jar


# REGLES DE DEPENDANCE #

## API ##
${BUILD}/API/MonPrint.class : ${SRC}/API/MonPrint.java 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/MonPrint.java

${BUILD}/API/TypeChambre.class : ${SRC}/API/TypeChambre.java 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/TypeChambre.java

${BUILD}/API/Chambre.class : ${SRC}/API/Chambre.java \
	  		     ${BUILD}/API/TypeChambre.class\
			     ${BUILD}/API/MonPrint.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/Chambre.java

${BUILD}/API/Client.class : ${SRC}/API/Client.java \
                            ${BUILD}/API/MonPrint.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/Client.java

${BUILD}/API/Prereservation.class : ${SRC}/API/Prereservation.java \
	  		            ${BUILD}/API/TypeChambre.class \
	  		     	    ${BUILD}/API/Client.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/Prereservation.java

${BUILD}/API/Reservation.class : ${SRC}/API/Reservation.java \
				${BUILD}/API/Chambre.class \
	  		         ${BUILD}/API/Prereservation.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/Reservation.java

${BUILD}/API/PrereservationFactory.class : ${SRC}/API/PrereservationFactory.java \
	  		            ${BUILD}/API/Prereservation.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/PrereservationFactory.java

${BUILD}/API/ReservationFactory.class : ${SRC}/API/ReservationFactory.java \
	  		            ${BUILD}/API/Reservation.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/API/ReservationFactory.java

## MNP ##

${BUILD}/MNP/ClientNP.class : ${SRC}/MNP/ClientNP.java \
                              ${BUILD}/API/Client.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/ClientNP.java

${BUILD}/MNP/ChambreNP.class : ${SRC}/MNP/ChambreNP.java \
                              ${BUILD}/API/Chambre.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/ChambreNP.java

${BUILD}/MNP/PrereservationNP.class : ${SRC}/MNP/PrereservationNP.java \
			${BUILD}/MNP/ClientNP.class \
                        ${BUILD}/API/Prereservation.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/PrereservationNP.java

${BUILD}/MNP/ReservationNP.class : ${SRC}/MNP/ReservationNP.java \
                              ${BUILD}/API/Reservation.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/ReservationNP.java

${BUILD}/MNP/PrereservationFactoryNP.class : ${SRC}/MNP/PrereservationFactoryNP.java \
                              ${BUILD}/API/PrereservationFactory.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/PrereservationFactoryNP.java

${BUILD}/MNP/ReservationFactoryNP.class : ${SRC}/MNP/ReservationFactoryNP.java \
			      ${BUILD}/MNP/ChambreNP.class \
			      ${BUILD}/MNP/ReservationNP.class \
                              ${BUILD}/API/ReservationFactory.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/ReservationFactoryNP.java

${BUILD}/MNP/BaseDonnee.class : ${SRC}/MNP/BaseDonnee.java
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/BaseDonnee.java

${BUILD}/MNP/Dessin.class : ${SRC}/MNP/Dessin.java \
            			${BUILD}/MNP/ReservationFactory.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/Dessin.java

${BUILD}/MNP/Reservations.class : ${SRC}/MNP/Reservations.java \
            			${BUILD}/MNP/PrereservationFactory.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/Reservations.java

${BUILD}/MNP/ReservationControlleur.class : ${SRC}/MNP/ReservationControlleur.java \
            			${BUILD}/MNP/Reservations.class \
            			${BUILD}/MNP/ReservationFactory.class \
            			${BUILD}/MNP/PrereservationFactory.class \
            			${BUILD}/MNP/BaseDonnee.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/ReservationControlleur.java


${BUILD}/MNP/Statistiques.class : ${SRC}/MNP/Statistiques.java \
            			${BUILD}/MNP/ReservationFactoryNP.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/Statistiques.java

${BUILD}/MNP/StatistiquesControlleur.class : ${SRC}/MNP/StatistiquesControlleur.java \
            			${BUILD}/MNP/ReservationFactoryNP.class \
            			${BUILD}/MNP/Statistiques.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/StatistiquesControlleur.java

${BUILD}/MNP/Graphique.class : ${SRC}/MNP/Graphique.java \
            			${BUILD}/MNP/BaseDonnee.class 
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/Graphique.java

${BUILD}/MNP/Controlleur.class : ${SRC}/MNP/Controlleur.java \
            			${BUILD}/MNP/ReservationFactoryNP.class \
            			${BUILD}/MNP/Graphique.class \
            			${BUILD}/MNP/Statistiques.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/Controlleur.java

${BUILD}/MNP/Booking.class : ${SRC}/MNP/Booking.java \
            			${BUILD}/MNP/BaseDonnee.class \
            			${BUILD}/MNP/Graphique.class \
            			${BUILD}/MNP/Controlleur.class
	${JAVAC} ${JAVAC_OPTIONS} ${SRC}/MNP/Booking.java


## TEST ##

 ${BUILD}/Test/TestTexteMNP.class : ${SRC}/Test/TestTexteMNP.java \
			 ${BUILD}/MNP/PrereservationNP.class \
			 ${BUILD}/MNP/PrereservationFactoryNP.class \
                         ${BUILD}/MNP/ReservationFactoryNP.class
	${JAVAC} -Xlint:deprecation ${JAVAC_OPTIONS} ${SRC}/Test/TestTexteMNP.java

# ## JARS ##

 ${JAR_MNP} : ${BUILD}/MNP/Booking.class
	${JAR} cvfe ${JAR_MNP} fr.iutfbleau.projetIHM2021FI2.MNP.Booking -C build fr

