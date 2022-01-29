#include "GlobalNamespace/ConditionalMaterialSwitcher.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/GamePause.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "include/Utilities/HookingUtility.hpp"
#include "include/Utilities/ClawUtils.hpp"

#include "include/main.hpp"

#include "UnityEngine/Transform.hpp"

MAKE_HOOK_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start,
                void, GlobalNamespace::SaberModelContainer* self) {
    SaberModelContainer_Start(self);

    auto saber = self->dyn__saber();
    auto model = self->dyn__saberModelControllerPrefab();

    auto saberTop = saber->dyn__saberBladeTopTransform();
    auto modelTop = model->get_transform();

    auto saberPos = saberTop->get_localPosition();
    auto modelScale = modelTop->get_localScale();

    saberPos.z = 0.3;
    modelScale.z = 0.3;
    modelScale.y = 0.3;
    modelScale.x = 0.3;

    saberTop->set_localPosition(saberPos);
    modelTop->set_localScale(modelScale);
    modelTop->set_localScale(modelScale);

    getLogger().info("length of model was: %.2f", modelScale.z);
}

void InstallClawHooks(Logger& logger) {
    INSTALL_HOOK(logger, SaberModelContainer_Start)
}

ClawsInstallHooks(InstallClawHooks);