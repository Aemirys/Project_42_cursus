/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:23:55 by estosche          #+#    #+#             */
/*   Updated: 2025/02/12 13:25:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <string>
#include "HttpResponse.hpp"
#include "utils.hpp"
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

class ErrorHandler {
public:
    static HttpResponse generateErrorResponse(int statusCode);
};

#endif
