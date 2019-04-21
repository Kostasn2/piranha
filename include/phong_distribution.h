#ifndef PHONG_DISTRIBUTION_H
#define PHONG_DISTRIBUTION_H

#include <microfacet_distribution.h>

namespace manta {

	class VectorNode;

	struct PhongMemory {
		math::real power;
	};

	class PhongDistribution : public MicrofacetDistribution {
	public:
		PhongDistribution();
		~PhongDistribution();

		virtual void initializeSessionMemory(const IntersectionPoint *surfaceInteraction, NodeSessionMemory *memory, StackAllocator *stackAllocator) const;

		virtual math::Vector generateMicrosurfaceNormal(NodeSessionMemory *mem) const;
		virtual math::real calculateDistribution(const math::Vector &m, NodeSessionMemory *mem) const;
		virtual math::real calculateG1(const math::Vector &v, const math::Vector &m, NodeSessionMemory *mem) const;

		void setPower(math::real power) { m_power = power; }
		math::real getPower() const { return m_power; }

		void setPowerNode(VectorNode *node) { m_powerNode = node; }
		VectorNode *getPowerNode() const { return m_powerNode; }

		void setMinMapPower(math::real power) { m_minMapPower = power; }
		math::real getMinMapPower() const { return m_minMapPower; }

	protected:
		VectorNode *m_powerNode;
		math::real m_power;
		math::real m_minMapPower;
	};

} /* namespace manta */

#endif /* PHONG_DISTRIBUTION_H */
