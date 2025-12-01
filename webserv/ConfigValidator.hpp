/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigValidator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:54 by estosche          #+#    #+#             */
/*   Updated: 2025/03/11 14:03:27 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_VALIDATOR_HPP
#define CONFIG_VALIDATOR_HPP

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "Config.hpp"

class ConfigValidator {
public:
    ConfigValidator(const Config& config);

    bool validate();

private:
    const Config& config;

    bool validatePorts();
    bool validateErrorPages();
    bool validateAllowedMethods();
};

#endif