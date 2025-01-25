// Copyright kiruru002. All Rights Reserved.

#include "ViewportWidgetsListFunctionLibrary.h"
#include "ViewportWidgetsList/Public/ViewportWidgetsList.h"
#include "Components/Widget.h"
#include "Components/PanelWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"

UWidget* UViewportWidgetsListFunctionLibrary::FindParentWidgetOfType(UWidget* StartingWidget, TSubclassOf<UWidget> Type)
{
    if (StartingWidget)
    {
        UPanelWidget* ParentPanel = StartingWidget->GetParent();
        if (ParentPanel)
        {
            UWidget* ParentWidget = Cast<UWidget>(ParentPanel);
            if (ParentWidget)
            {
                if (ParentWidget->IsA(Type))
                {
                    return ParentWidget;
                }
                return FindParentWidgetOfType(ParentWidget, Type);
            }
        }
        UObject* OuterObject = StartingWidget->GetOuter();
        if (OuterObject)
        {
            UWidget* ParentUserWidget = Cast<UUserWidget>(OuterObject->GetOuter());
            if (ParentUserWidget && ParentUserWidget->IsA(Type))
            {
                return ParentUserWidget;
            }
            return FindParentWidgetOfType(ParentUserWidget, Type);
        }
    }
    return nullptr;
}
