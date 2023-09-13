#include "Material.h"

#include "Shader.h"
#include "Texture.h"

namespace GLI
{
	Material::~Material()
	{
		for (const auto& property : properties)
		{
			delete property;
		}
	}

	void Material::Activate() const
	{
		shader->Bind();
		for (const auto& property : properties)
		{
			property->UseProperty(*shader);
		}
	}

	Material::PropertySampler2D* Material::MakeProperty(const std::string& name, Texture* sampler, int&& value)
	{
		return new PropertySampler2D{ name, sampler, std::forward<int>(value) };
	}

	void Material::UpdateProperty(const std::string& name, Texture* sampler, int&& value)
	{
		PropertySampler2D* property = CastProperty(GetProperty(name));
		property->sampler = sampler;
		property->values = { std::forward<int>(value)};
	}

	bool Material::ContainsProperty(const std::string& name) const
	{
		auto it = std::find_if(
			properties.begin(), properties.end(),
			[&name](const PropertyBase* property)
			{
				return property->name == name;
			}
		);

		return it != properties.end();
	}

	Material::PropertyBase* Material::GetProperty(const std::string& name) const
	{
		auto it = std::find_if(
			properties.begin(), properties.end(),
			[&name](const PropertyBase* property)
			{
				return property->name == name;
			}
		);

		if (it == properties.end())
			throw nullptr;

		return *it;
	}

	template<>
	Material::Property<float>* Material::CastProperty<float>(PropertyBase* property)
	{
		return dynamic_cast<Property<float>*>(property);
	}

	Material::PropertySampler2D* Material::CastProperty(PropertyBase* property)
	{
		return dynamic_cast<PropertySampler2D*>(property);
	}

	template<>
	void Material::Property<int>::UseProperty(Shader& shader)
	{
		switch (values.size())
		{
		case 1:
			shader.SetUniform1i(name, &values[0]);
			break;
		case 2:
			//shader.SetUniform2i(name, &values[0]);
			break;
		case 3:
			//shader.SetUniform3i(name, &values[0]);
			break;
		case 4:
			//shader.SetUniform4i(name, &values[0]);
			break;
		}
	}

	template<>
	void Material::Property<float>::UseProperty(Shader& shader)
	{
		switch (values.size())
		{
		case 1:
			//shader.SetUniform1f(name, &values[0]);
			break;
		case 2:
			//shader.SetUniform2f(name, &values[0]);
			break;
		case 3:
			//shader.SetUniform3f(name, &values[0]);
			break;
		case 4:
			shader.SetUniform4f(name, &values[0]);
			break;
		}
	}

	Material::PropertySampler2D::PropertySampler2D(const std::string& name, Texture* sampler, int&& value) :
		sampler{ sampler },
		Property<int>(name, { std::forward<int>(value) })
	{
	}

	void Material::PropertySampler2D::UseProperty(Shader& shader)
	{
		Property<int>::UseProperty(shader);
		sampler->Activate();
	}
}
