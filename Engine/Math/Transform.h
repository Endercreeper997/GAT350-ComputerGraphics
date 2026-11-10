#pragma once
#include "Serialization/Json.h"
#include "Vector2.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/norm.hpp>

namespace nu
{
    struct Transform
    {
        glm::vec3 position{ 0.0f };
        glm::vec3 rotation{ 0.0f }; // degrees
        glm::vec3 scale{ 1.0f };

        glm::mat4 matrix;

        glm::mat4 GetMatrix() const
        {
            auto mxt = glm::translate(position);
            auto mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
            auto mxs = glm::scale(scale);


            return mxt * mxr * mxs;
        }

        glm::vec3 Forward() const 
        { 
            auto mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
            return mxr * glm::vec4{ 0, 0, 1, 0 };
        }

        glm::vec3 Up() const
        {
            auto mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
            return mxr * glm::vec4{ 0, 1, 0, 0 };
        }

        glm::vec3 Right() const
        {
            auto mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
            return mxr * glm::vec4{ 1, 0, 0, 0 };
        }

        void Read(const json::value_t& value)
        {
            JSON_READ(value, position);

            //glm::vec3 euler;
            JSON_READ(value, rotation);
            JSON_READ(value, scale);
        }
    };
}