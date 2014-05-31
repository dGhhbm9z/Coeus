#include "CustomComponents.h"
#include "PortDefinitions.h"

CustomMenuBarButton::CustomMenuBarButton(ButtonType btntype) {
	switch (btntype) {
	case AccountChartType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/AccountChart.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/AccountChart.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/AccountChart.png"));
		break;
	case CompaniesType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Companies.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Companies.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Companies.png"));
		break;
	case CustomersType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Customers.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Customers.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Customers.png"));
		break;
	case EventsType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Events.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Events.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Events.png"));
		break;
	case SuppliersType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Suppliers.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Suppliers.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Suppliers.png"));
		break;
	case BusinessModelType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/BusinessModelCanvas.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/BusinessModelCanvas.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/BusinessModelCanvas.png"));
		break;
	case BusinessPlanType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/BusinessPlan.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/BusinessPlan.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/BusinessPlan.png"));
		break;
	case FinancialRatiosType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/FinancialRatios.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/FinancialRatios.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/FinancialRatios.png"));
		break;
	case OpenSourceInnovationType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/OpenSourceInno.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/OpenSourceInno.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/OpenSourceInno.png"));
		break;
	case ReportGeneratorTytpe:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/ReportGenerator.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/ReportGenerator.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/ReportGenerator.png"));
		break;
	case LogoutType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Logout/LogoutNormal.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Logout/MouseOver.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Logout/MouseClick.png"));
		break;
	case AccountingTabType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Accounting/AccountingTabNormal.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Accounting/AccountingTabNormalMouseOver.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Accounting/AccountingTabSelected.png"));
		break;
	case ReportingTabType:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Reporting/ReportingTabNormal.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Reporting/ReportingTabNormalMouseOver.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Reporting/ReportingTabSelected.png"));
		break;
	default:
		imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Suppliers.png"));
		imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Suppliers.png"));
		imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Suppliers.png"));
	}
}

void CustomMenuBarButton::paint(Graphics &g) {

	if (isMouseButtonDown()) {
		g.drawImage(imageMouseDown, 0, 0, getWidth(), getHeight(), 0, 0, imageMouseDown.getWidth(), imageMouseDown.getHeight());
	}
	else if (isMouseOver()) {
		g.drawImage(imageMouseOver, 0, 0, getWidth(), getHeight(), 0, 0, imageMouseOver.getWidth(), imageMouseOver.getHeight());
	}
	else {
		g.drawImage(imageNormal, 0, 0, getWidth(), getHeight(), 0, 0, imageNormal.getWidth(), imageNormal.getHeight());
	}
}

//=======================================================================================

CustomTabContent::CustomTabContent() {
	title = new Label("", "Events");
	title->setFont(22);
	title->setJustificationType(Justification::centred);

	search = new TextEditor();
	search->setFont(Font(22));
	search->setTextToShowWhenEmpty(L"Enter Search Keyword", Colours::black.withAlpha(0.5f));

	addAndMakeVisible(title);
	addAndMakeVisible(search);
}

CustomTabContent::~CustomTabContent()
{
	title = nullptr;
	search = nullptr;
}

void CustomTabContent::resized()
{
	title->setBoundsRelative(0.5f - 0.125f, 0.01, 0.25f, 0.05f);
	search->setBoundsRelative(0.5f - 0.125f, 0.01 + 0.05f, 0.25f, 0.05f);
}

Rectangle<int> CustomTabContent::getComponentArea()
{
	return Rectangle<int>(0.01f*getWidth(), 0.15f*getHeight(), getWidth() - 0.01f*getWidth(), getHeight() - 0.15f*getHeight());
}