#pragma once

#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace GLI
{
	class Shader;
	class Texture;

	class Material
	{
	private:

		struct PropertyBase
		{
			std::string name;

			PropertyBase(const std::string& name) :
				name{ name }
			{
			}

			virtual ~PropertyBase() = 0 {}
			virtual void UseProperty(Shader& shader) = 0;
		};

		Shader* shader;

		std::vector<PropertyBase*> properties;
	
	public:

		template<typename T>
		struct Property : PropertyBase
		{
			std::vector<T> values;

			Property(const std::string& name, const std::vector<T>& values) :
				values{ values },
				PropertyBase(name)
			{
			}

			virtual ~Property() override {}

			virtual void UseProperty(Shader& shader) override;
		};

		struct PropertySampler2D : Property<int>
		{
			Texture* sampler;

			PropertySampler2D(const std::string& name, Texture* sampler, int&& value);

			virtual ~PropertySampler2D() override {}
			virtual void UseProperty(Shader& shader) override;
		};

		template<typename... Params>
		Material(Shader* shader, Params&&... args) :
			shader{ shader }
		{
			properties = { std::forward<Params>(args)... };
		}
		
		virtual ~Material();
		
		virtual void Activate() const;

		template<typename T, typename... Params>
		static Property<T>* MakeProperty(const std::string& name, T&& value, Params&&... args)
		{
			return new Property<T>{ name, { std::forward<T>(value), std::forward<Params>(args)... } };
		}

		static PropertySampler2D* MakeProperty(const std::string& name, Texture* sampler, int&& value);

		template<typename T, typename... Params>
		void UpdateProperty(const std::string& name, T&& value, Params&&... args)
		{
			auto property = CastProperty<std::remove_reference<T&&>::type>(GetProperty(name));
			property->values = { std::forward<T>(value), std::forward<Params>(args)... };
		}

		void UpdateProperty(const std::string& name, Texture* sampler, int&& value);

		inline const Shader* GetShader() const { return shader; }

	private:

		bool ContainsProperty(const std::string& name) const;

		PropertyBase* GetProperty(const std::string& name) const;

		template<typename T>
		Property<T>* CastProperty(PropertyBase* property);

		PropertySampler2D* CastProperty(PropertyBase* property);
	};
}

