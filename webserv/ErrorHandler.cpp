/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:25:59 by estosche          #+#    #+#             */
/*   Updated: 2025/02/17 12:54:50 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorHandler.hpp"
#include <fstream>
#include <sstream>

HttpResponse ErrorHandler::generateErrorResponse(int statusCode) {
    HttpResponse response(statusCode);  // Crée une réponse avec le code de statut approprié

    // Définir les fichiers d'erreur
    std::string errorPagesDir = "errors/";
    std::map<int, std::string> errorPages;
    errorPages.insert(std::make_pair(400, "400.html"));
    errorPages.insert(std::make_pair(403, "403.html"));
    errorPages.insert(std::make_pair(404, "404.html"));
    errorPages.insert(std::make_pair(405, "405.html"));
    errorPages.insert(std::make_pair(500, "500.html"));
    errorPages.insert(std::make_pair(503, "503.html"));

    // Chercher le fichier d'erreur associé au code
    std::string filePath = errorPagesDir + errorPages[statusCode];

    // Lire le fichier d'erreur
    std::ifstream file(filePath.c_str());
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();  // Lire tout le fichier dans le buffer
        response.setBody(buffer.str());  // Définir le corps de la réponse avec le contenu du fichier
    } else {
        // Si le fichier d'erreur n'est pas trouvé, générer un message d'erreur par défaut
        std::string defaultError = "<html><body><h1>Error ";
        
        // Convertir le statusCode en string sans std::to_string
        std::ostringstream oss;
        oss << statusCode;
        defaultError += oss.str();

        defaultError += "</h1><p>The error page for this status code could not be loaded.</p></body></html>";
        response.setBody(defaultError);  // Utiliser le message par défaut
    }

    // Définir les en-têtes HTTP (Content-Type et Content-Length)
    response.setHeader("Content-Type", "text/html");

    // Utilisation de std::ostringstream pour obtenir la taille du corps
    std::ostringstream lengthStream;
    lengthStream << response.getBodyLength();  // Calculer la longueur du corps
    response.setHeader("Content-Length", lengthStream.str());  // Définir l'en-tête Content-Length

    return response;
}


// HttpResponse ErrorHandler::generateErrorResponse(int statusCode) {
//     HttpResponse response;
//     response.setStatusCode(statusCode);

//     // Définir les fichiers d'erreur
//     std::string errorPagesDir = "errors/";
//     std::map<int, std::string> errorPages;
//     errorPages.insert(std::make_pair(400, "400.html"));
//     errorPages.insert(std::make_pair(403, "403.html"));
//     errorPages.insert(std::make_pair(404, "404.html"));
//     errorPages.insert(std::make_pair(400, "405.html"));
//     errorPages.insert(std::make_pair(500, "500.html"));
//     errorPages.insert(std::make_pair(503, "503.html")); // Ajout de 503 si tu veux gérer ce code aussi

//     // Chercher le chemin du fichier d'erreur
//     std::string filePath = errorPagesDir + errorPages[statusCode];

//     // Lire le fichier d'erreur
//     std::ifstream file(filePath.c_str());
//     if (file.is_open()) {
//         std::stringstream buffer;
//         buffer << file.rdbuf();
//         response.setBody(buffer.str());
//     } else {
//         // Si le fichier d'erreur n'est pas trouvé, générer un message d'erreur par défaut
//         std::string defaultError = "<html><body><h1>Error " + intToString(statusCode) + "</h1><p>The error page for this status code could not be loaded.</p></body></html>";
//         response.setBody(defaultError);
//     }

//     // Définir les en-têtes HTTP
//     response.setHeader("Content-Type", "text/html");

//     // Utilisation de std::ostringstream pour obtenir la taille du corps
//     std::ostringstream lengthStream;
//     lengthStream << response.getBodyLength();
//     response.setHeader("Content-Length", lengthStream.str());

//     return response;
// }