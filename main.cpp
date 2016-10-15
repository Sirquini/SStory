/*
 * main.cpp
 * Interactive CLI Text Adventure using OpenAl for sounds.
 * 
 * Author: Santiago Quintero
 * Released under The MIT License
 *
 */

#include "sstory.h"

int main ()
{
    SStory myStory;

    // Test of the different feactures of SStory library.
    myStory.addScene("START",
    {
        SContentBody("Es poco despues de las 12 de la noche. Te encuentras manejando, en medio de la nada, camino a casa despues de una reunion con tus viejos amigos en la ciudad vecina.", 2),
        SContentBody("El camino se encuentra mas vacio que de costumbre, y la monotonia de los arboles a cada lado hace creer que el camino no termina. Tal vez sea bueno para un momento.",{
            SChoice("LLEGADA", "Detenerme en el camino", "Un poco de aire fresco podria ayudar, llevas manejando varias horas y decides detenerte un poco mas adelante."),
            SChoice("LLEGADA", "Seguir manejando", "Tal vez despues, el camino es muy largo aun. Un poco mas adelante decides detenerte un momento, algo no esta bien con el carro.")
        })
    });
    myStory.addScene("LLEGADA",{
        SContentBody("Te detienes a un lado del camino. Al salir notas el silencio que cubre todo el bosque, un escenario perfecto para una caminata. Como siempre, nunca hay red en estas zonas.", 3),
        SContentBody("Decides marcar donde parqueaste y tomar una corta caminata por el bosque. Despues de un rato el camino que seguias se combierte en tres. ", 11),
        SContentBody(" El primero parece poco obstruido y aclarado por la luz de la luna llena. \n El segundo parece estar cubierto por mas arboles. \n El tercero, parece descender y reflejos de luz se ven a lo lejos."),
        SContentBody("Cual tomar?", {
            SChoice("CAM1", "El primer camino"),
            SChoice("CAM2", "El segundo camino"),
            SChoice("CAM3", "El tercer camino")
        })
    });
    myStory.addScene("CAM1",{
        SContentBody("Te adentras en el camino, la luna esta especialmente brillante, cada detalle del camino resalta.", 12),
        SContentBody("Despues de caminar un rato por escuchas el aullido de un animal, muy probablemente un lobo. Logras detectar el lugar del que parece provenir, que deseas hacer.", {
            SChoice("WOLF", "Investigar el ruido"),
            SChoice("CAM2", "Alejarse del ruido", "Desides alejar del ruido y retornar el camino, no mucho tiempo pasas hasta que llegas a un nuevo sendero en un denso bosque")
        }, 8)
    });
    myStory.addScene("CAM2",{
        SContentBody("A pesar de lo frondoso del bosque, puedes escuchar la naturaleza que habita el ajeno lugar. Una calma se apodera de tu cuerpo mientras continuas haciendo camino.", 5),
        SContentBody("La calma se siente cortada al escuchar un disparo a la distancia, quien mas podria estar en este lugar?", {
            SChoice("CAM3", "Investigar el origen del disparo", "Te acercas al lugar donde crees que proviene el primer disparo, en frente hay un joven cazador y a la distancia un ciervo. \n\nEl cazador voltea a verte e indica que hagas silencio, pero el ciervo se escapa. El cazador, triste de haber perdido a su presa, se acerca y te orienta a un claro donde dice pasa un rio. Insiste en que es mas seguro ahí, ya que en el espeso bosque podría haberte confundido con un ciervo."),
            SChoice("HUNT", "Seguir en el camino")
        }, 7)
    });
    myStory.addScene("CAM3",{
        SContentBody("Descendiendo por el camino, llegas al claro de un rio.", 10),
        SContentBody("La vista es bastante tranquila, el ruido del rios se combina con la luz de la luna, y el cielo esta lleno de estrellas, unas mas grandes que otras."),
        SContentBody("Te recuestas y contemplas la calma del lugar y las distintas constelaciones que puedes armar con las distintas estrellas. Casi nunca tienes este tipo de oportunidad.", {
            SChoice("FINAL", "Dormir un rato"),
            SChoice("INF", "Volver al carro")
        }, 9)
    });
    myStory.addScene("FINAL",{
        SContentBody("Cierras los ojos y duermes.", 9),
        SContentBody("Sientes que el frio de la noche se vuelve salido. Al despertar notas que te encuentras de regreso en el asiento de pasajero del carro."),
        SContentBody("Inicias el motor y retomas tu camino a casa.",4),
        SContentBody("Poco despues ves un letrero que indica el desvio a casa. Curiosamente notas que el bosque se acaba en el letrero, como si alguien separara los dos lugares con un regla imaginaria. La red regresa y las notificaciones empiezan a llegar.", 13),
        SContentBody("A pasado una semana.")
    });
    myStory.addScene("INF",{
        SContentBody("Te levantas y retomas tu camino de regreso al carro.", 11),
        SContentBody("El camino de regreso se ve distinto del que hablas recorrido, pero no le das mucha importancia."),
        SContentBody("Enciendes el carro y retomas tu camino a casa.", 4),
        SContentBody("Las horas pasan y sientes que ya has pasado por los mismos lugares y los mismos arboles, hasta que detallas que mas adelante están las marcas de la vez que te detuviste a caminar.", 2)
    });
    myStory.addScene("WOLF",{
        SContentBody("Al acercarte, un nuevo aullido se escucha aun mas cerca que antes, pero del lado opuesto, casi como si la criatura supiera que la estas buscando.", 13),
        SContentBody("Un nuevo ruido, esta vez mas agersivo se escucha muy cerca, tal vez esta no era una muy buena idea después de todo.", 6),
        SContentBody("Un lobo salta y ataca desde los arbustos, no hay mucho que puedas hacer, un ataque por sorpresa.", 0)
    });
    myStory.addScene("HUNT",{
        SContentBody("Continuas normal con tu camino."),
        SContentBody("Otro disparo, pero esta vez te deja si alientos. Al revisarte, ves como la sangre empieza a fluir del pecho a travez de la ropa.", 7)
    });
    
    myStory.play();

    return 0;
}
