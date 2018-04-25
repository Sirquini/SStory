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
    SStory::Story myStory;

    // Test of the different feactures of SStory library.
    myStory.addScene("START",
    {
        SStory::ContentBody("Es poco después de las 12 de la noche. Te encuentras manejando, en medio de la nada, camino a casa después de una reunión con tus viejos amigos en la ciudad vecina.", SSound::Sample::driving),
        SStory::ContentBody("El camino se encuentra más vacío que de costumbre, y la monotonía de los árboles a cada lado da la sensación de que el camino no termina. Tal vez sea bueno parar un momento.",{
            SStory::Choice("LLEGADA", "Detenerme en el camino", "Un poco de aire fresco podría ayudar. Llevas manejando varias horas y decides detenerte un poco más adelante."),
            SStory::Choice("LLEGADA", "Seguir manejando", "Tal vez después, el camino es muy largo aún. Un poco más adelante decides detenerte un momento, algo no está bién con el carro.")
        })
    });
    myStory.addScene("LLEGADA",{
        SStory::ContentBody("Te detienes a un lado del camino. Al salir notas el silencio que cubre todo el bosque, un escenario perfecto para una caminata. Como siempre, nunca hay red en estas zonas.", SSound::Sample::engine_off),
        SStory::ContentBody("Decides marcar donde parqueaste y tomar una corta caminata por el bosque. Después de un rato el camino que seguías se divide en tres. ", SSound::Sample::walking),
        SStory::ContentBody(" El primero parece poco obstruido y aclarado por la luz de la luna llena.\n El segundo parece estar cubierto por más árboles.\n El tercero, parece descender y reflejos de luz se ven a lo lejos."),
        SStory::ContentBody("¿Cuál tomar?", {
            SStory::Choice("CAM1", "El primer camino"),
            SStory::Choice("CAM2", "El segundo camino"),
            SStory::Choice("CAM3", "El tercer camino")
        })
    });
    myStory.addScene("CAM1",{
        SStory::ContentBody("Te adentras en el camino, la luna está especialmente brillante, cada detalle del suelo resalta.", SSound::Sample::wolf, SSound::Channel::background),
        SStory::ContentBody("Después de caminar un rato escuchas el aullido de un animal, muy probablemente un lobo. Logras detectar el lugar del que parece provenir el ruido. ¿Qué deseas hacer?", {
            SStory::Choice("WOLF", "Investigar el ruido"),
            SStory::Choice("CAM2", "Alejarse del ruido", "Decides alejarte del ruido y retornar al camino, no mucho tiempo pasa hasta que llegas a un nuevo sendero en un denso bosque")
        }, SSound::Sample::howl, SSound::Channel::right)
    });
    myStory.addScene("CAM2",{
        SStory::ContentBody("A pesar de lo frondoso del bosque, puedes escuchar la naturaleza que habita el ajeno lugar. Una calma se apodera de tu cuerpo mientras continuas haciendo camino.", SSound::Sample::forest, SSound::Channel::background),
        SStory::ContentBody("La calma se siente cortada al escuchar un disparo a la distancia. ¿Quién más podría estar en este lugar?", {
            SStory::Choice("CAM3", "Investigar el origen del disparo", "Te acercas al lugar donde crees que provino el primer disparo, en frente hay un joven cazador y a la distancia un ciervo. \n\nEl cazador voltea a verte e indica que hagas silencio, pero el ciervo se escapa. El cazador, triste de haber perdido a su presa, se acerca y te orienta a un claro donde dice que pasa un río. Insiste en que es más seguro ahí, ya que en el espeso bosque podría haberte confundido con un ciervo."),
            SStory::Choice("HUNT", "Seguir en el camino")
        }, SSound::Sample::gun, SSound::Channel::right)
    });
    myStory.addScene("CAM3",{
        SStory::ContentBody("Descendiendo por el camino, llegas al claro de un rio.", SSound::Sample::river, SSound::Channel::left),
        SStory::ContentBody("La vista es bastante tranquila, el ruido del río se combina con la luz de la luna, y el cielo está lleno de estrellas, unas más grandes que otras."),
        SStory::ContentBody("Te recuestas y contemplas la calma del lugar y las distintas constelaciones que puedes armar con las distintas estrellas. Casi nunca tienes este tipo de oportunidad.", {
            SStory::Choice("FINAL", "Dormir un rato"),
            SStory::Choice("INF", "Volver al carro")
        }, SSound::Sample::piano, SSound::Channel::background)
    });
    myStory.addScene("FINAL",{
        SStory::ContentBody("Cierras los ojos y duermes.", SSound::Sample::piano, SSound::Channel::background),
        SStory::ContentBody("Sientes que el frío de la noche se vuelve sólido. Al despertar notas que te encuentras de regreso en el asiento de pasajero del carro."),
        SStory::ContentBody("Inicias el motor y retomas tu camino.",SSound::Sample::engine_on),
        SStory::ContentBody("Poco después ves un letrero que indica el desvío a casa. Curiosamente notas que el bosque se acaba en el letrero, como si alguien separara los dos lugares con un regla imaginaria. La red del celular regresa y las notificaciones empiezan a llegar.", SSound::Sample::carby),
        SStory::ContentBody("A pasado una semana.")
    });
    myStory.addScene("INF",{
        SStory::ContentBody("Te levantas y retomas tu camino de regreso al carro.", SSound::Sample::walking),
        SStory::ContentBody("El camino de regreso se ve distinto del que habías recorrido, pero no le das mucha importancia."),
        SStory::ContentBody("Enciendes el carro y retomas tu camino a casa.", SSound::Sample::engine_on),
        SStory::ContentBody("Las horas pasan y sientes que ya has pasado por los mismos lugares y los mismos árboles, hasta que detallas que más adelante están las marcas de la vez que te detuviste a caminar.", SSound::Sample::driving)
    });
    myStory.addScene("WOLF",{
        SStory::ContentBody("Al acercarte, un nuevo aullido se escucha aun más cerca que antes, pero del lado opuesto, casi como si la criatura supiera que la estas buscando.", SSound::Sample::howl, SSound::Channel::left),
        SStory::ContentBody("Un nuevo ruido, esta vez más agersivo se escucha muy cerca, tal vez ésta no era una muy buena idea después de todo.", SSound::Sample::growl),
        SStory::ContentBody("Un lobo salta y ataca desde los arbustos, no hay mucho que puedas hacer, un ataque por sorpresa.", SSound::Sample::attack)
    });
    myStory.addScene("HUNT",{
        SStory::ContentBody("Continuas normal con tu camino."),
        SStory::ContentBody("Otro disparo, pero esta vez te deja sin alientos. Al revisarte, ves como la sangre empieza a fluir del pecho a travez de la ropa.", SSound::Sample::gun, SSound::Channel::right),
        SStory::ContentBody("Te sientes frío, y la oscuridad lo cubre todo.")
    });
    
    myStory.play();

    return 0;
}
