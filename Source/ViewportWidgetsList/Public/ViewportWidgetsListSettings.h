// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Templates/SubclassOf.h"
#include "Components/Widget.h"
#include "EditorUtilityWidgetBlueprint.h"
#include <map>
#include <memory>
#include <string>
#include "ViewportWidgetsListSettings.generated.h"

USTRUCT()
struct VIEWPORTWIDGETSLIST_API FViewportWidgetsListSettingsEntry
{
    GENERATED_BODY()
public:

    // �E�B�W�F�b�g�̃\�t�g�Q��
    // Soft object reference to the widget
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings")
    TSoftObjectPtr<UEditorUtilityWidgetBlueprint> Widget;

    // �T�u���j���[�̖��O�B�R���}��s���I�h���g�p���ĊK�w��\���ł��܂��B
    // Name of the sub-menu. Hierarchies can be represented using commas or periods.
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings")
    FName SubMenuName;

    // ���j���[���ڃZ�N�V�����̖��O
    // Name of the menu item
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings")
    FName SectionName;

    // ���j���[���ڂ̃e�L�X�g
    // Label of the menu item
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings")
    FText Label;

    // ���j���[���ڂ̃c�[���`�b�v
    // Tooltip of the menu item
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings")
    FText TooltipText;

    // ���j���[���ڂ̃e�L�X�g (�f�t�H���g)
    // Label of the menu item (Default)
    UPROPERTY(VisibleAnywhere, Category = "UViewportWidgetsListSettings")
    FText DefaultLabel;

    // ���j���[���ڂ̃c�[���`�b�v (�f�t�H���g)
    // Tooltip of the menu item (Default)
    UPROPERTY(VisibleAnywhere, Category = "UViewportWidgetsListSettings")
    FText DefaultTooltipText;

public:
    FViewportWidgetsListSettingsEntry() = default;
    FViewportWidgetsListSettingsEntry(TSoftObjectPtr<UEditorUtilityWidgetBlueprint> Widget, FName SubMenuName, FName SectionName, FText Label, FText TooltipText, FText DefaultLabel, FText DefaultToolTipText);
};

namespace ViewportWidgetsListSettings
{
    class Node : public std::enable_shared_from_this<Node>
    {
    public:
        TArray<const FViewportWidgetsListSettingsEntry*> Entries;
        // �q
        std::map<std::string, std::shared_ptr<Node>> Children;
        // �q���擾�i���݂��Ȃ��ꍇ�͍쐬�j
        std::shared_ptr<Node> GetChild(const std::string& name);
        std::shared_ptr<Node> GetChildPath(const std::string& path);
    };
}

UCLASS(config = EditorPerProjectUserSettings)
class VIEWPORTWIDGETSLIST_API UViewportWidgetsListUserSettings : public UObject
{
    GENERATED_BODY()
public:
    // �r���[�|�[�g�E�B�W�F�b�g���X�g�v���O�C����L���ɂ���
    // Enable the viewport widgets list plugin
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings", meta = (ConfigRestartRequired = true))
    bool bEnableViewportWidgetsListPlugin;

public:
    UViewportWidgetsListUserSettings();
};

UCLASS(config = ViewportWidgetsListSettings, DefaultConfig)
class VIEWPORTWIDGETSLIST_API UViewportWidgetsListSettings : public UObject
{
    GENERATED_BODY()
public:
    // �㕔���j���[�ɒǉ����鍀�ڂ̖��O
    // Name of the viewport widgets list menu
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings", meta = (ConfigRestartRequired = true))
    FText ViewportWidgetsListMenuName;

    // �㕔���j���[�ɒǉ����鍀�ڂ̐�����
    // Description of the viewport widgets list menu
    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings", meta = (ConfigRestartRequired = true))
    FText ViewportWidgetsListMenuTooltip;

    UPROPERTY(EditAnywhere, config, Category = "UViewportWidgetsListSettings", meta = (ConfigRestartRequired = true))
    TArray<FViewportWidgetsListSettingsEntry> ViewportWidgetsListMenuProvidedWidgets;

    std::shared_ptr<ViewportWidgetsListSettings::Node> HierarchyRoot;

public:
    UViewportWidgetsListSettings();
    void FixDefaultTexts();
    virtual void PostInitProperties() override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
};
